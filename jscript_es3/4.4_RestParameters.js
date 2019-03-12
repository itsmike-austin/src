function max(...numbers) {
    let result = -Infinity;
    for( let number of numbers ) {
	if ( number > result ) result = number;
    }
    return result;
}

console.log("max(...numbers) for (4,1,9,-2): " + max(4,1,9,-2));
