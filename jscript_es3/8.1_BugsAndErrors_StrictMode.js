"use strict";
function canYouSpotTheProblem() {
    "use strict";
    for( let counter = 0 ; counter < 10 ; ++counter ) {
	console.log("Happy happy");
    }
}

canYouSpotTheProblem();

function Person(name) { this.name = name; }
let ferdinand = Person("Ferdinand");
console.log(name);
