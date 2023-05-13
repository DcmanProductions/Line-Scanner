package main

import (
    "fmt"
    "io/ioutil"
    "path/filepath"
    "strings"
    "time"
)

type fileData struct {
    Lines      int
    Extension  string
    Characters int64
    Files      int
}

func main() {
    start := time.Now()
    fileDataList := getLines()

    for _, data := range fileDataList {
        fmt.Printf("\033[32m%s:\033[0m\n", data.Extension)
        fmt.Printf("\033[36m\t- %d Line(s)\n\033[0m", data.Lines)
        fmt.Printf("\033[33m\t- %d Character(s)\n\033[0m", data.Characters)
        fmt.Printf("\033[35m\t- %d File(s)\n\033[0m", data.Files)
    }

    elapsed := time.Since(start)
    fmt.Printf("Process finished after %v\n", elapsed)
}

func getLines() []fileData {
    files, _ := ioutil.ReadDir(".")
    var fileDataList []fileData

    for _, file := range files {
        if !file.IsDir() {
            contents, _ := ioutil.ReadFile(file.Name())
            extension := strings.ToLower(filepath.Ext(file.Name()))

            var existing *fileData
            for i := range fileDataList {
                if fileDataList[i].Extension == extension {
                    existing = &fileDataList[i]
                    break
                }
            }

            lines := strings.Count(string(contents), "\n")
            characters := int64(len(contents))
            files := 1

            if existing != nil {
                lines += existing.Lines
                characters += existing.Characters
                files += existing.Files

                for i := range fileDataList {
                    if fileDataList[i].Extension == extension {
                        fileDataList = append(fileDataList[:i], fileDataList[i+1:]...)
                        break
                    }
                }
            }

            fileDataList = append(fileDataList, fileData{
                Lines:      lines,
                Extension:  extension,
                Characters: characters,
                Files:      files,
            })
        }
    }

    return fileDataList
}
