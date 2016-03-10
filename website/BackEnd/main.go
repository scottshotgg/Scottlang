package main

import (
	"fmt"
	"log"
	"net/http"
	"html/template"
	"encoding/json"
)

type genericResponse struct {
	Success bool   `json:"success"`
	Err     string `json:"err"`
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


func main() {
	http.Handle("/resources/", http.StripPrefix("/resources/", http.FileServer(http.Dir("resources")))) 
	http.HandleFunc("/", hello)

	exe_cmd("ls -la")
	log.Println("ls")
	http.ListenAndServe(":8080", nil)

}