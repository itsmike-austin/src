function greaterThan(n) {
    return m => m > n;
}

let greaterThan10 = greaterThan(10);
console.log(greaterThan10(11));

function noisy(f) {
    return (...args) => {
	console.log("calling with ", args);
	let result = f(...args);
	console.log("called with ", args, ", returned", result)
	return result;
    };
}

noisy(Math.min)(3,2,1);

["A", "B"].forEach(l => console.log(l));
