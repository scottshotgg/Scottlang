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

func main() {
	http.Handle("/resources/", http.StripPrefix("/resources/", http.FileServer(http.Dir("resources")))) 
	http.HandleFunc("/", hello)
	http.ListenAndServe(":8080", nil)
}