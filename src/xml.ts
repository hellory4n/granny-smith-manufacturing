import { isAlphanumeric, StringMap } from "./lib";

export interface XmlNode {
	tag: string;
	attributes: StringMap<string>;
	/**
	 * null if there's children nodes
	 */
	content?: string;
	/**
	 * empty if there's string content
	 */
	children: XmlNode[];
	// internal
	endingTag: boolean;
}

/**
 * definitely non-standard xml parser implementation
 */
class XmlParser {
	src: string;
	position: number = 0;
	line: number = 0;

	constructor(src: string) {
		this.src = src;
	}

	error(msg: string): void {
		throw `at line ${this.line}: ${msg}`;
	}

	atEnd(): boolean {
		return this.position >= this.src.length;
	}

	expect(char: string): void {
		if (this.atEnd()) {
			this.error(`expected ${char}, got EOF`);
		}
		if (this.src.charAt(this.position) !== char) {
			this.error(`expected ${char}, got ${this.src.charAt(this.position)}`);
		}
		this.position++;
	}

	/**
	 * get current character, returns \0 on eof
	 */
	peek(): string {
		if (this.atEnd()) {
			return "\0";
		}
		return this.src.charAt(this.position);
	}

	/**
	 * get next character, returns \0 on eof
	 */
	peekNext(): string {
		if (this.position + 1 >= this.src.length) {
			return "\0";
		}
		return this.src.charAt(this.position + 1);
	}

	advance(): string {
		if (this.atEnd()) {
			return "\0";
		}
		return this.src.charAt(this.position++);
	}

	// skips all whitespace where it is allowed
	whitespace(): void {
		while (!this.atEnd()) {
			// const char C referece
			// referenecce to the C prgrammin langguag
			const char = this.peek();
			if (char === "\n") {
				this.line++;
			}
			if (char !== " " && char !== "\t" && char !== "\r" && char !== "\n") {
				break;
			}
		}
	}

	identifier(): string {
		const start = this.position;
		while (isAlphanumeric(this.peek())) {
			this.advance();
		}
		return this.src.substring(start, this.position);
	}

	parseNode(): XmlNode {
		let node: XmlNode = {
			tag: "",
			attributes: {},
			children: [],
			endingTag: false,
		};

		this.expect("<");
		if (this.peek() == "/") {
			node.endingTag = true;
		}
		node.tag = this.identifier();
		if (node.endingTag) {
			this.whitespace();
			this.expect(">");
			return node;
		}
		this.whitespace();

		while (!this.atEnd()) {
			// self-closing tag
			if (this.peek() === "/" && this.peekNext() === ">") {
				this.advance();
				this.advance();
				return node;
			}

			// has children/string content
			if (this.peek() === ">") {
				this.advance();
				this.whitespace();

				// children
				// TODO consider not using insalubrious levels of indentation
				if (this.peek() === "<") {
					while (true) {
						if (this.atEnd()) {
							this.error(
								"expected ending tag, found EOF",
							);
						}
						const child = this.parseNode();
						if (child.endingTag) {
							return node;
						} else {
							node.children.push(child);
						}
					}
				}
				// string content
				else {
					const start = this.position;
					while (this.peek() !== "<" && this.peekNext() !== "/") {
						if (this.atEnd()) {
							this.error(
								"expected ending tag, found EOF",
							);
						}
						this.advance();
					}

					node.content = this.src.substring(start, this.position);

					// consume ending tag
					this.whitespace();
					this.expect("<");
					this.expect("/");
					this.identifier();
					this.expect(">");
					return node;
				}
			}

			// attributes
			if (isAlphanumeric(this.peek())) {
				const attr = this.identifier();
				this.whitespace();
				this.expect("=");
				this.whitespace();
				this.expect('"');

				// fuck escape sequences
				const valStart = this.position;
				while (this.peek() !== '"') {
					this.advance();
				}
				const val = this.src.substring(valStart, this.position);
				node.attributes[attr] = val;
			}

			this.whitespace();
		}

		this.error("expected tag end, got EOF");
		return node;
	}
}

export class XmlDocument {
	private _root: XmlNode;

	constructor(src: string) {
		if (src.length === 0) {
			throw "empty xml document";
		}

		const parser = new XmlParser(src);
		this._root = parser.parseNode();
	}

	root(): XmlNode {
		return this._root;
	}
}
