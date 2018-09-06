//
// theImageFactory.js
//
var imgk  = require('imagemagick');
var md5   = require('md5');
var fs    = require('fs');
var path  = require('path');

var basedir = path.dirname(__filename) + "/fonts/";
var ERROR_IMG = fs.readFileSync(path.dirname(__filename) + "/error.png");
// Number-ordering for font type (16 selected)
var fonttypes = [
"ahronbd.ttf", "andlso.ttf",   "BOD_BLAR.TTF",
"BOOKOSB.TTF",  "BRITANIC.TTF", "BRLNSB.TTF",   "BRLNSDB.TTF",
"BROADW.TTF",   "PALSCRI.TTF",  "phagspab.ttf", "plantc.ttf",
"PRISTINA.TTF", "SketchFlow Print.ttf", "upcjb.ttf",    "upclb.ttf",
"verdanab.ttf"
];

// Sizes as reference for switch construction
var fontsizes = ["16", "24", "32", "40", "48"];

// Accessing colors by their names
var RGBcolors = {
    blanco:"#FFFFFF",   negro:"#000000",   rojo:"#FF0000",
    verde:"#00FF00",    azul:"#0000FF",    magenta:"#FF00FF",
    celeste:"#00C89B",  gris:"#BEBEBE",    salmon:"#FA8072",
    naranja:"#FFA500",  coral:"#FF7F50",   tomate:"#FF6347",
    rosa:"#FFC0CB",     marron:"#B03060",  orquidea:"#DA70D6"
};

function Image(text, font, size, colour) {
	this.text = text;
	this.font = font;
	this.siz = size;
	this.colour = colour;
	this.image = undefined;
	this.md5 = undefined;
	this.setMD5 = function(h) {this.md5 = h}
	this.setImage = function(i) {this.image = i}
	this.size = function() {return this.image.length}
	this.img = function() {return this.image}
	this.hash = function() {return this.md5}
}


// Main class
//exports.Label = function (texto, fuente, tam, color, cb) {
function Label (texto, fuente, tam, color, cb) {
    var myImage = new Image(texto,fuente,tam,color);
    function valid () {
        /* 
        Limitations:
        texto.length < 200
        fuente in [1, fonttypes[].length] (subset of the whole fonts space)
        tam in fontsizes[] subset
        color in listaRGBcolors[] subset
        */
        if ((texto.length >= 200) || (fuente < 1) || (fuente > fonttypes.length)) {
            return false;
        } else {
            switch (tam) {
                case "16":
                case "24":
                case "32":
                case "40":
                case "48":
                    return (RGBcolors[color] !== undefined);
                    break;
                default:
                    return false;
            }
        }
    }

    function labelBuild_png () {
        // parameter check was performed before, so we don't need to do it again

        var fontname = fonttypes[parseInt(fuente, 10) - 1];
		console.log("Entro a imgk.convert");
      
        imgk.convert(['-density', '72x72', '-background', 'transparent', '-fill',
                      RGBcolors[color], '-gravity',  'Center', '-pointsize', tam,
                      '-font', basedir + fontname, 'label:' + texto, 'png:'],
        		function (err, stdout) {
console.log("In imgk.convert callback...", err, stdout);
				if (err) myImage.setImage( ERROR_IMG ); // handcrafted error handling
				else myImage.setImage( new Buffer(stdout, 'binary') );
                		cb (err, myImage);
			})
    } // labelBuild_png
    myImage.setMD5( md5(fonttypes[1 + parseInt(fuente,10)] + tam + color + texto) );
    if (!valid()) {
      myImage.setImage( ERROR_IMG );
      cb (true, myImage);
    }
    else labelBuild_png();  //this.imgLength = this.img.byteLength;
} // Label
        
module.exports.Label=Label;
module.exports.Image=Image;
