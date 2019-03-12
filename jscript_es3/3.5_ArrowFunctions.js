const power = (base,exponent) => {
    let result = 1;
    for( let count=0 ; count < exponent ; ++count ) {
	result *= base;
    }
    return result;
}

const square1 = (x) => { return x*x; }
const square2 = x => x * x;

const horn = () => { console.log("Toot"); };

console.log("arrowPower(3,4): " + power(3,4));
console.log("square1(2):      " + square1(2));
console.log("square2(4):      " + square2(4));
console.log("horn();"); horn();
