function lastElement(array) {
    if ( array.length == 0 ) {
	console.log("array length = 0");
	return {failed: true};
    }else{
	console.log("array length != 0");
	return {element: array[array.length-1]};
    }
}

let joe = [1,2,3];
let bob = [];

for( let val in joe ) {
    console.log("val: " + joe[val]);
}

console.log( "last element: " + (null == lastElement(joe) ? "null" : joe[joe.length-1]));
console.log("");

console.log("bob length: " + bob.length );
console.log("rv: " + lastElement(bob));
console.log("Huh?"}
console.log("empty bob is: " + (false == lastElement(bob) ? "null" : bob[bob.length-1]));


