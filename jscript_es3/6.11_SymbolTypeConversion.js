class Rabbit {
    constructor(type) {
	this.type = type;
    }
    speak(line) {
	console.log(`The ${this.type} rabbit says '${line}'`);
    }
}

let killerRabbit = new Rabbit("killer");
let blackRabbit  = new Rabbit("black");

let sym = Symbol("name");
console.log(sym == Symbol("name"));
Rabbit.prototype[sym] = 55;
console.log("Black Rabbit Symbol: ",blackRabbit[sym]);

const toStringSymbol = Symbol("toString");
Array.prototype[toStringSymbol] = function() {
    return `${this.length} cm of blue yarn`;
};

console.log([1,2].toString());
console.log([1,2][toStringSymbol]());

let stringObject = {
    [toStringSymbol]() { return "a jute rope"; }
};
console.log(stringObject[toStringSymbol]());
