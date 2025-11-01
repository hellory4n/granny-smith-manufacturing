package manufacturing

// assertma balls
func Assert(msg string, x bool) {
	if !x {
		panic("failed assert: " + msg)
	}
}
