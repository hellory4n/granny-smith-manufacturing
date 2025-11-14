#!/usr/bin/env python3
import elderlystudio as es
import sys

def main():
	# TODO real cli interface (command line interface interface)
	level: es.LevelFile = es.level_from_svg(sys.argv[1])
	es.save_level_file(sys.argv[2], level)

if __name__ == "__main__":
	main()
