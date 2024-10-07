var canvas = document.querySelector("#c");

var gl = canvas.getContext("webgl");
if (!gl) {
    console.log("No WebGL?");
}