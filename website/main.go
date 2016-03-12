package main

import (
	"fmt"
	"log"
	"net/http"
	"html/template"
	"encoding/json"
	"sync"
	"strings"
	"os/exec"
	"os"
	"io/ioutil"
	"strconv"

		// this is for the live server version to determine what directory 
				// it needs to use and where it is in relation to the lexer
)

type commandResponse struct {
	Command string	`json:"command"`
	Output string	`json:"output"`
}

type commandRequest struct {
	Command string `json:"commandToParse"`
}

type genericResponse struct {
	Success bool   `json:"success"`
}

type GenericHandler struct {
	GET  func(http.ResponseWriter, *http.Request)
	PUT  func(http.ResponseWriter, *http.Request)
	POST func(http.ResponseWriter, *http.Request)
}


var live int = 0



func hello(w http.ResponseWriter, r *http.Request) {
	templatePath := fmt.Sprintf("index.html")
	t, err := template.ParseFiles(templatePath)
	if err != nil {
		log.Printf("Error parsing template at %s\n", templatePath)
		log.Println(err)
		response, _ := json.Marshal(genericResponse{Success: true})
		w.Write(response)
		return
	}
	log.Println("executing ...");
	t.Execute(w, nil)
}

func exe_cmd(parts []string, wg *sync.WaitGroup) (ss string) {

	fmt.Println("command is ", parts)
	// splitting head => g++ parts => rest of the command
	//parts := strings.Fields(cmd)

	//log.Println(parts)

	head := parts[0]
	parts = parts[1:len(parts)]

	out, err := exec.Command(head,parts...).Output()
	if err != nil {
		fmt.Printf("%s", err)
	}
	//fmt.Printf("%s", out)
	wg.Done() // Need to signal to waitgroup that this goroutine is done

	ss = string(out[:len(out)])

	return
}

func app(w http.ResponseWriter, r *http.Request) {

	/*request := &commandRequest{}

	log.Println(r.Body)

	thisisanerror := json.NewDecoder(r.Body).Decode(request)

	fmt.Println("in the function and shit", thisisanerror)
	
	log.Println(request.Command)*/
	r.ParseForm()

	//addPresetRequest := &addPresetData{}
	//err := json.NewDecoder(r.Body).Decode(addPresetRequest)
	//stringthing := r.Form["commmand"]
	//log.Println(stringthing)


	//d1 := []byte("")
    //errr := ioutil.WriteFile("../program1", d1, 0644)
    //check(errr)

    //me := "./../lexical \"[" + r.Form["command"] + "]\" 0"

    // use a more efficient one later, too lazy right now to deal with that parsing each char shit, i hate golang for this stuff


    me := fmt.Sprintf("%s", r.Form["commandToParse"])

	log.Println(me)

    amount := len(strings.Split(me, " "))

    if(amount > 3) {
    	me = fmt.Sprintf("%s", r.Form["commandToParse"])
    }

    log.Println(me);

	log.Println("Lexing command....")
	var wg sync.WaitGroup
    wg.Add(1)

    stringForCommand := []string{"gcc", "./../lexical", "-o lexical"}

    if(live == 1) {
    stringForCommand = []string{"gcc", "./lexical", "-o lexical"}
    }


	exe_cmd(stringForCommand, &wg)			// this will not need to run everytime
	wg.Add(1)

//	stringForCommandAmount := (len(r.Form["command"]))

	command := append([]string{}, r.Form["command"]...)

	log.Println(command)

	//command := string(byte(r.Form["command"])[:stringForCommandAmount])

	stringForCommand[0] = stringForCommand[1]
	stringForCommand[1] = me
	stringForCommand[2] = "0"

	out := exe_cmd(stringForCommand, &wg)		// for now dont modify it, but later we 
															// should modify so that something in 
															// quotes will be interpreted differently

	log.Println("Done lexing the command!")

	var stringy []byte

	if(live == 1) {
		stringy, _ = ioutil.ReadFile("program")
    } else {
    	stringy, _ = ioutil.ReadFile("../program")
    }
	s := string(stringy[:len(stringy)])

	log.Println("\n\n" + s, out)


	response, _ := json.Marshal(commandResponse{Command: s, Output: out})
	w.Write(response)

}

func (this GenericHandler) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	//sessionCookie, _ := req.Cookie("session")
	//host, _, _ := net.SplitHostPort(req.RemoteAddr)
	/*
		If we're at the same IP address as the server, the host should be ::1 (ipv6 localhost)
	*/
	//switch {
	//case host == "::1":		// this currently only works on chrome for some reason
		/*
			The request is coming from the server. Let it through by default.
		*/
	//case sessionCookie == nil || !database.IsSessionHashValid(sessionCookie.Value):
	//	redirectToLoginHandler(w, req)
	//	log.Println("Redirected to login")
	//	return
	//}

	/*
		Generic stuff goes here
	*/
		
	if req.Method == "GET" && this.GET != nil {
		this.GET(w, req)
	} else if req.Method == "POST" && this.POST != nil {
		this.POST(w, req)
	} else if req.Method == "PUT" && this.PUT != nil {
		this.PUT(w, req)
	} else {
		http.Error(w, "GenericHandler error", http.StatusInternalServerError)
		log.Fatalf("No handler specified for the request %s", req)
	}
}

func main() {
	
    fmt.Println(len(os.Args), os.Args)

    log.Println(os.Args[2])

    live, _ = strconv.Atoi(os.Args[2])
    //live = i

	log.SetFlags(log.LstdFlags | log.Lshortfile)
	http.Handle("/resources/", http.StripPrefix("/resources/", http.FileServer(http.Dir("resources")))) 
	http.HandleFunc("/", hello)
	http.Handle("/app", GenericHandler{PUT: app})			/// I might do this, kinda weird though
	//http.HandleFunc("/app", app)
	http.ListenAndServe(":8080", nil)

}