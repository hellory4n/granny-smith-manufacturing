import { Level } from "./level";

/**
 * typescript really doesn't like global variables
 */
export interface Context {
	current_level?: Level;
}
