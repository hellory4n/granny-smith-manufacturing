package main

import (
	"fmt"
	"os"

	"github.com/hellory4n/granny-smith-manufacturing/manufacturing"
)

func main() {
	// TODO gui
	if len(os.Args) == 0 {
		manufacturing.CmdHelp()
		os.Exit(0)
	}

	var output string
	var input string
	for i, arg := range os.Args {
		// first arg is the cmd path
		if i == 0 {
			continue
		}

		switch arg {
		case "--help", "-h":
			manufacturing.CmdHelp()
			os.Exit(0)
		case "--version", "-v":
			manufacturing.CmdVersion()
			os.Exit(0)
		case "--verbose":
			manufacturing.Ctx.Verbose = true
		case "-o":
			if i < len(os.Args)-1 {
				output = os.Args[i+1]
			} else {
				fmt.Println("error: expected output path")
				os.Exit(1)
			}
		default:
			if input == "" {
				if arg != output {
					input = arg
				}
			} else {
				fmt.Println("error: there can only be one input")
				os.Exit(1)
			}
		}
	}

	if input == "" || output == "" {
		manufacturing.CmdHelp()
		os.Exit(0)
	}
	manufacturing.CmdGenerateLevel(input, output)
}
