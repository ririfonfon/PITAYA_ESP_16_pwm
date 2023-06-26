window.addEventListener('load', setup);

var connection;

function connect() {

    `use strict`;
    function refreshTime() {
        const timeDisplay = document.getElementById("time");
        const dateString = new Date().toLocaleString();
        const formattedString = dateString.replace(", ", " - ");
        timeDisplay.textContent = formattedString;
    }
    setInterval(refreshTime, 1000);

    console.log('connect()');
    connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

    connection.onopen = function () {
        connection.send('Connect ' + new Date());
    };

    connection.onmessage = function (e) {
        console.log('Server: ', e.data);

        if (e.data.charAt(0) == 'cc') {
            var data = e.data.split(':');
            document.getElementById(data[0]).value = data[1];
        } //if

        if (e.data.charAt(0) == 'mem') {
            var val = e.data.split(':')[1];
            var elems = document.querySelectorAll('#mode li a');
            [].forEach.call(elems, function (el) {
                el.classList.remove('active');
            });
            document.getElementById(val).classList.add('active');
        } //if

        if (e.data.charAt(0) == 'b') {

            if (e.data.charAt(1) == 'b') {
                var data = e.data.split(':');
                document.getElementById('cc2').value = data[1];
            } //if b

            if (e.data.charAt(1) == 'd') {
                var data = e.data.split(':');
                document.getElementById('cc4').value = data[1];
            } //if d

            if (e.data.charAt(1) == 'e') {
                var data = e.data.split(':');
                document.getElementById('cc5').value = data[1];
            } //if e

            if (e.data.charAt(1) == 'f') {
                var data = e.data.split(':');
                document.getElementById('cc6').value = data[1];
            } //if f

        } //if b

        if (e.data.charAt(0) == 'd') {

            if (e.data.charAt(1) == '1') {
                var data = e.data.split('/');
                document.getElementById('daySu0').value = data[1];
            }

            if (e.data.charAt(1) == '2') {
                var data = e.data.split('/');
                document.getElementById('dayMo0').value = data[1];
            }

            if (e.data.charAt(1) == '3') {
                var data = e.data.split('/');
                document.getElementById('dayTu0').value = data[1];
            }
            if (e.data.charAt(1) == '4') {
                var data = e.data.split('/');
                document.getElementById('dayWe0').value = data[1];
            }

            if (e.data.charAt(1) == '5') {
                var data = e.data.split('/');
                document.getElementById('dayTh0').value = data[1];
            }

            if (e.data.charAt(1) == '6') {
                var data = e.data.split('/');
                document.getElementById('dayFr0').value = data[1];
            }

            if (e.data.charAt(1) == '7') {
                var data = e.data.split('/');
                document.getElementById('daySa0').value = data[1];
            }
        } //if d

        if (e.data.charAt(0) == 'c') {
            if (e.data.charAt(1) == 'o'){
                var data = e.data.split('/');
                document.getElementById('on_time').value = data[1]; 
            }
            if (e.data.charAt(1) == 'f'){
                var data = e.data.split('/');
                document.getElementById('off_time').value = data[1];  
            }

        }

    }; //function (e)

    connection.onclose = function (e) {
        console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);
        connection.close();
        setTimeout(function () {
            connect();
        }, 1000);
    };

    connection.onerror = function (err) {
        console.error('Socket encountered error: ', err.message, 'Closing socket');
        connection.close();
        setTimeout(function () {
            connect();
        }, 1000);
    };
}

connect();

id_array = new Array('cc1');
values = new Array(id_array.length);




////////////////////////////////////////////////////////////////prepare

function prepareVar2() {
    var a = parseInt(document.getElementById('cc2').value).toString(8);
    if (a.length < 2) { a = '0' + a; }
    values = a;
    var data = "bb" + values;
    console.log('fData: ' + data);
    connection.send(data);
} //prepare 2

function prepareVar4() {
    var a = parseInt(document.getElementById('cc4').value).toString(8);
    if (a.length < 2) { a = '0' + a; }
    values = a;
    var data = "bd" + values;
    console.log('hData: ' + data);
    connection.send(data);
} //prepare 4

function prepareVar5() {
    var a = parseInt(document.getElementById('cc5').value).toString(8);
    if (a.length < 2) { a = '0' + a; }
    values = a;
    var data = "be" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 5

function prepareVar6() {
    var a = parseInt(document.getElementById('cc6').value).toString(8);
    if (a.length < 2) { a = '0' + a; }
    values = a;
    var data = "bf" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 6


function prepareVar12() {
    // var a = parseInt(document.getElementById('off_time').value).toString();
    var a = document.getElementById('on_time').value;
    // if (a.length < 4) { a = '000' + a; }
    values = a;
    var data = "co/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 12

function prepareVar13() {
    // var a = parseInt(document.getElementById('off_time').value).toString();
    var a = document.getElementById('off_time').value;
    // if (a.length < 4) { a = '000' + a; }
    values = a;
    var data = "cf/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 13

function prepareVar21() {
    var a = document.getElementById('daySu0').checked;
    values = a;
    var data = "d1/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 21

function prepareVar22() {
    var a = document.getElementById('dayMo0').checked;
    values = a;
    var data = "d2/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 22

function prepareVar23() {
    var a = document.getElementById('dayTu0').checked;
    values = a;
    var data = "d3/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 23

function prepareVar24() {
    var a = document.getElementById('dayWe0').checked;
    values = a;
    var data = "d4/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 24

function prepareVar25() {
    var a = document.getElementById('dayTh0').checked;
    values = a;
    var data = "d5/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 25

function prepareVar26() {
    var a = document.getElementById('dayFr0').checked;
    values = a;
    var data = "d6/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 26

function prepareVar27() {
    var a = document.getElementById('daySa0').checked;
    values = a;
    var data = "d7/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 27


function submitVal(name, val) {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', 'set?' + name + '=' + val, true);
    xhttp.send();
} //submitVal

function handle_M_B_S(e) {
    e.preventDefault();
    var name = e.target.className;
    var val = e.target.id;
    console.log('name: ' + name);
    console.log('val: ' + val);

    if (e.target.className.indexOf('mem') > -1) {
        elems = document.querySelectorAll('#mode li a');
        [].forEach.call(elems, function (el) {
            el.classList.remove('active');
            name = e.target.className;
        });
        e.target.classList.add('active');
    }
    submitVal(name, val);

    // SAVE: send clock
    if (val == 1) {
        let clock = Math.floor(Date.now() / 1000); // now in seconds since 1970
        submitVal('clock', clock);
        console.log('clock: ' + clock);
    }

} //handle_M_B_S

function rgbToHsl(r, g, b) {
    console.log('rgbToHsl(r, g, b)');
    r = r / 255;
    g = g / 255;
    b = b / 255;
    var max = Math.max(r, g, b);
    var min = Math.min(r, g, b);
    var h, s, l = (max + min) / 2;
    if (max == min) {
        h = s = 0;
    } else {
        var d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        switch (max) {
            case r:
                h = (g - b) / d + (g < b ? 6 : 0);
                break;
            case g:
                h = (b - r) / d + 2;
                break;
            case b:
                h = (r - g) / d + 4;
                break;
        }
        h = h / 6;
    }
    return [h, s, l];
}

function setup() {
    console.log('setup()');
    var xhttp = new XMLHttpRequest();

    elems = document.querySelectorAll('ul li a'); // adds listener
    [].forEach.call(elems, function (el) {
        // el.addEventListener('touchstart', handle_M_B_S, false);
        el.addEventListener('click', handle_M_B_S, false);
    });
    submitVal("mem", 0);
}

function RGBToHex(r, g, b) {
    if (r.length == 0) r = "00"
    if (g.length == 0) g = "00"
    if (b.length == 0) b = "00"

    r = parseInt(r).toString(16);
    g = parseInt(g).toString(16);
    b = parseInt(b).toString(16);

    if (r.length == 1) r = "0" + r;
    if (g.length == 1) g = "0" + g;
    if (b.length == 1) b = "0" + b;

    return "#" + r + g + b;
}

function hexToRGB(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}