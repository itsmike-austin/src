window.requestAnimFrame = (function () {
    return window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || window.oRequestAnimationFrame || window.msRequestAnimationFrame || function (callback) {
        window.setTimeout(callback, 1000 / 60);
    };
})();

var canvas = document.getElementById("canvas"); //create variable canvas
context = canvas.getContext("2d"); //create variable cx
function bubble(x, y, r) {
    var randx = Math.floor(Math.random() * canvas.width - 50); //random on the x axis
    var randy = Math.floor(Math.random() * canvas.height + 200); //random on the y axis
    this.x = randx || x || 0; //this.x = a random x on the canvas
    this.y = randy || y || 0; //this.y = the top y position of the canvas
    this.r = r || 0; //this.r = specified by me
    this.expired = false; //set expired for the bubble to false
    this.color = "green";

    this.draw = function () { //create the draw function
        context.beginPath();
        context.arc(this.x, this.y, this.r, 0, 2 * Math.PI, false); //fill the circle
        context.fillStyle = this.color; //set the inside of the bubble to blue
        context.fill();
        context.lineWidth = 1;
        context.strokeStyle = "black";
        context.stroke();
    };


    this.update = function () { //create the function for update
        this.y--; //everytime this function runs, move the bubble up the y axis by one
        if (y < canvas.height) { //if the y axis of the bubble is less than the height of the canvas
            this.expired = true; //make the bubble disappear
        }
    };

    // HITTEST: Perform hit-test to determine if the passed in coordinate lies within 
    // the circle.
    // http://stackoverflow.com/questions/2212604/javascript-check-mouse-clicked-inside-the-circle-or-polygon
    this.hitTest = function (x, y) {
        var dx = x - this.x
        var dy = y - this.y
        return dx * dx + dy * dy <= this.r * this.r
    };
}

var bubbles = new Array(); //create a new array for the bubbles
function newBubble() { //create function for a new bubble
    bubbles.push(new bubble(window.randx, window.randy, 30));
}

var time = 0;

function loop() {
    context.clearRect(0, 0, canvas.width, canvas.height); //clear the canvas
    if (time % 10 === 0) { //if the time is directly divisable into 0 make a new bubble
        newBubble(); //create a new bubble
    }

    for (var i = 0, l = bubbles.length; i < l; i++) {
        bubbles[i].update();
        bubbles[i].draw();
        if (bubbles[i].expired) {
            bubbles.splice(i, 1);
            i--;
        }

    }

    time++;
    requestAnimFrame(loop);
}
loop();


// HITTEST: To convert the mouse position to be canvas relative.
// BEGIN http://stackoverflow.com/questions/1114465/getting-mouse-location-in-canvas
stylePaddingLeft = parseInt(document.defaultView.getComputedStyle(canvas, null)['paddingLeft'], 10) || 0;
stylePaddingTop = parseInt(document.defaultView.getComputedStyle(canvas, null)['paddingTop'], 10) || 0;
styleBorderLeft = parseInt(document.defaultView.getComputedStyle(canvas, null)['borderLeftWidth'], 10) || 0;
styleBorderTop = parseInt(document.defaultView.getComputedStyle(canvas, null)['borderTopWidth'], 10) || 0;

// Some pages have fixed-position bars (like the stumbleupon bar) at the top or left of the page
// They will mess up mouse coordinates and this fixes that
var html = document.body.parentNode;
htmlTop = html.offsetTop;
htmlLeft = html.offsetLeft;


function getMouse(e, canvas) {
    var element = canvas,
        offsetX = 0,
        offsetY = 0,
        mx, my;

    // Compute the total offset. It's possible to cache this if you want
    if (element.offsetParent !== undefined) {
        do {
            offsetX += element.offsetLeft;
            offsetY += element.offsetTop;
        } while ((element = element.offsetParent));
    }

    // Add padding and border style widths to offset
    // Also add the <html> offsets in case there's a position:fixed bar (like the stumbleupon bar)
    // This part is not strictly necessary, it depends on your styling
    offsetX += stylePaddingLeft + styleBorderLeft + htmlLeft;
    offsetY += stylePaddingTop + styleBorderTop + htmlTop;

    mx = e.pageX - offsetX;
    my = e.pageY - offsetY;

    // We return a simple javascript object with x and y defined
    return {
        x: mx,
        y: my
    };
};
// END http://stackoverflow.com/questions/1114465/getting-mouse-location-in-canvas

// HITTEST: Here is an event handler to perform hit-testing on bubbles.
canvas.onmousemove = function (e) {
    var pt = getMouse(e, canvas);
    for (var i = 0, l = bubbles.length; i < l; i++) {
        if (bubbles[i].hitTest(pt.x, pt.y)) 
            bubbles[i].color = "red";  // Set the color to red to demonstrate the "hit"
    }
}
