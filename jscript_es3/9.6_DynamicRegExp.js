let name = "harry";
let text = "Harry is a suspicious character.";
let regexp = new RegExp("\\b(" + name + ")\\b", "gi");
console.log(text.replace(regexp,"_$1_"));
// _Harry_ is a suspicious character

let newName = "dea+hl[]rd";
let newText = "This dea+lh[]rd guy is super annoying.";
let escaped = newName.replace(/[\\[.+*?(){|^$]/g, "\\$&");
let newRegexp = new RegExp("\\b" + escaped + "\\b", "gi");
console.log("escaped: " + escaped);
console.log(newText.replace(newRegexp,"_$&_"));
