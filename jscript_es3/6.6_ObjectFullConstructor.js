class SomeClass {
    
    constructor(type) {
	this.type = type;
	this.a    = 1;
	this.b    = 2;
	this.c    = 3;
	this.l    = 4;
    }

    dumpvars() {
	console.log("a: " + this.a);
	console.log("b: " + this.b);
	console.log("c: " + this.c);
	console.log("l: " + this.l);
    }

};

let k = new SomeClass("Test");

k.dumpvars();

k.a = 4;
k.b = 8;

k.dumpvars();
