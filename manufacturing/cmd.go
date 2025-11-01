package manufacturing

import (
	"fmt"
)

func CmdVersion() {
	fmt.Println("granny smith manufacturing v0.0.3")
}

func CmdHelp() {
	fmt.Println("Usage: granny-smith-manufacturing <input svg> <output xml>")
	fmt.Println()
	fmt.Println("Flags:")
	fmt.Println("    --help, -h:    prints this")
	fmt.Println("    --version, -v: prints the current version")
	fmt.Println("    --verbose:     enables verbose output (for debugging)")
}

func CmdGenerateLevel(inputPath string, outputPath string) {
	fmt.Printf("fuck... %v %v\n", inputPath, outputPath)
}
