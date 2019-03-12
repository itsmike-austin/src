class Matrix {
    constructor(width,height,element=(x,y)=>undefined) {
	this.width   = width;
	this.height  = height;
	this.content = [];

	for( let y=0 ; y < height ; ++y ) {
	    for( let x=0 ; x < width ; ++x ) {
		this.content[y*width+x] = element(x,y);
	    }
	}
    }

    get(x,y) {
	return this.content[y*this.width+x];
    }

    set(x,y,value) {
	this.content[y*this.width+x] = value;
    }
}

class MatrixIterator {
    constructor(matrix) {
	this.x = 0;
	this.y = 0;
	this.matrix = matrix;
    }

    next() {
	if ( this.y == this.matrix.height ) return {done: true};

	let value = {x: this.x,
		     y: this.y,
		     value: this.matrix.get(this.x,this.y)};

	this.x++;

	if ( this.x == this.matrix.width ) {
	    this.x = 0;
	    this.y++;
	}

	return { value, done: false };
    }
}

Matrix.prototype[Symbol.iterator] = function() {
    return new MatrixIterator(this);
}

class SymetricMatrix extends Matrix {
    constructor(size, element=(x,y)=>undefined) {
	super(size,size,(x,y)=> {
	    if ( x < y ) return element(y,x);
	    else return element(x,y);
	});
    }

    set(x,y,value) {
	super.set(x,y,value);
	if ( x != y ) {
	    super.set(y,x,value);
	}
    }
}

console.log("instanceof determines if an object is an instance of a class");
console.log("Getting instanceof SymetricMatrix");
console.log("Is a SymetricMatrix an instanceof SymetricMatrix?");
console.log(new SymetricMatrix(2) instanceof SymetricMatrix);
console.log("Is a SymetricMatrix an instance of a matrix?");
console.log(new SymetricMatrix(2) instanceof Matrix);
console.log("Is a matrix an instance of a SymetricMatrix?");
console.log(new Matrix(2,2) instanceof SymetricMatrix);
console.log("Is an array an instance of an array?");
console.log([1] instanceof Array);


