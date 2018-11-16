$(function(){
    // This demo depends on the canvas element
    if(!('getContext' in document.createElement('canvas'))){
        alert('Sorry, it looks like your browser does not support canvas!');
        return false;
    }
    var doc = $(document),
           win = $(window),
           canvas = $('#paper'),
           ctx = canvas[0].getContext('2d'),
           instructions = $('#instructions'),
           id = Math.round($.now()*Math.random()), // Generate an unique ID
           drawing = false, // A flag for drawing activity
           clients = {},
           cursors = {},
           prev = {};
    canvas.on('mousedown',function(e){
        e.preventDefault();
        drawing = true;
        prev.x = e.pageX;
        prev.y = e.pageY;
    });
    doc.bind('mouseup mouseleave',function(){
        drawing = false;
    });
    doc.on('mousemove',function(e){
        // Draw a line for the current user's movement
        if(drawing){
            drawLine(prev.x, prev.y, e.pageX, e.pageY);
            prev.x = e.pageX;
            prev.y = e.pageY;
        }
    });
    function drawLine(fromx, fromy, tox, toy){
        ctx.moveTo(fromx, fromy);
        ctx.lineTo(tox, toy);
        ctx.stroke();
    }
});
