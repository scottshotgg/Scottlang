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
)

type genericResponse struct {
	Success bool   `json:"success"`
}

type GenericHandler struct {
	GET  func(http.ResponseWriter, *http.Request)
	PUT  func(http.ResponseWriter, *http.Request)
	POST func(http.ResponseWriter, *http.Request)
}

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
	log.Println("executing...");
	t.Execute(w, nil)
}

func exe_cmd(cmd string, wg *sync.WaitGroup) {
	fmt.Println("command is ",cmd)
	// splitting head => g++ parts => rest of the command
	parts := strings.Fields(cmd)
	head := parts[0]
	parts = parts[1:len(parts)]

	out, err := exec.Command(head,parts...).Output()
	if err != nil {
		fmt.Printf("%s", err)
	}
	fmt.Printf("%s", out)
	wg.Done() // Need to signal to waitgroup that this goroutine is done
}

func app(w http.ResponseWriter, r *http.Request) {
	fmt.Println("in the function and shit")
	r.ParseForm()
	log.Println(r.Form)
	response, _ := json.Marshal(genericResponse{Success: true})
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
	http.Handle("/resources/", http.StripPrefix("/resources/", http.FileServer(http.Dir("resources")))) 
	http.HandleFunc("/", hello)
	//http.Handle("/app", GenericHandler{GET: app})
	http.HandleFunc("/app", app)

	var wg sync.WaitGroup
    wg.Add(1)
   /* wg.Add(1)
    go dosomething(400, &wg)
    wg.Add(1)
    go dosomething(150, &wg)
    wg.Add(1)
    go dosomething(600, &wg)

    wg.Wait()
    fmt.Println("Done")*/

	exe_cmd("./../lexical ../program 0", &wg)
	http.ListenAndServe(":8080", nil)

}