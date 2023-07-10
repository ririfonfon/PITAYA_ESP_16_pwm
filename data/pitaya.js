window.addEventListener('load', setup);

var connection;

`use strict`;
function refreshTime() {
    const timeDisplay = document.getElementById("time");
    const dateString = new Date().toLocaleString();
    const formattedString = dateString.replace(", ", " - ");
    timeDisplay.textContent = formattedString;
}

function connect() {

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
                if (data[1] == 'true') {
                    document.getElementById('daySu0').checked = true;
                }
                else {
                    document.getElementById('daySu0').checked = false;
                }
            }

            if (e.data.charAt(1) == '2') {
                var data = e.data.split('/');
                if (data[1] == 'true') {
                    document.getElementById('dayMo0').checked = true;
                }
                else {
                    document.getElementById('dayMo0').checked = false;
                }
            }

            if (e.data.charAt(1) == '3') {
                var data = e.data.split('/');
                if (data[1] == 'true') {
                    document.getElementById('dayTu0').checked = true;
                }
                else {
                    document.getElementById('dayTu0').checked = false;
                }
            }
            if (e.data.charAt(1) == '4') {
                var data = e.data.split('/');
                if (data[1] == 'true') {
                    document.getElementById('dayWe0').checked = true;
                }
                else {
                    document.getElementById('dayWe0').checked = false;
                }
            }

            if (e.data.charAt(1) == '5') {
                var data = e.data.split('/');
                if (data[1] == 'true') {
                    document.getElementById('dayTh0').checked = true;
                }
                else {
                    document.getElementById('dayTh0').checked = false;
                }
            }

            if (e.data.charAt(1) == '6') {
                var data = e.data.split('/');
                if (data[1] == 'true') {
                    document.getElementById('dayFr0').checked = true;
                }
                else {
                    document.getElementById('dayFr0').checked = false;
                }
            }

            if (e.data.charAt(1) == '7') {
                var data = e.data.split('/');
                if (data[1] == 'true') {
                    document.getElementById('daySa0').checked = true;
                }
                else {
                    document.getElementById('daySa0').checked = false;
                }
            }
        } //if d

        if (e.data.charAt(0) == 'c') {
            if (e.data.charAt(1) == 'o') {
                var data = e.data.split('/');
                document.getElementById('on_time').value = data[1];
            }
            if (e.data.charAt(1) == 'f') {
                var data = e.data.split('/');
                document.getElementById('off_time').value = data[1];
            }

        }

        setInterval(refreshTime, 1000);

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
    var a = document.getElementById('on_time').value;
    values = a;
    var data = "co/" + values;
    console.log('iData: ' + data);
    connection.send(data);
} //prepare 12

function prepareVar13() {
    var a = document.getElementById('off_time').value;
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
        let utc = new Date();
        let offset = utc.getTimezoneOffset();
        let clock = Math.floor(new Date(utc.getTime() - offset * 60000) / 1000); // now in seconds since 1970 + time zone
        //   let clocko = Math.floor((Date.now()) / 1000); // now in seconds since 1970
        submitVal('clock', clock);
        console.log('clock: ' + clock);
        console.log('offset: ' + offset);
    }

} //handle_M_B_S

function setup() {
    console.log('setup()');
    var xhttp = new XMLHttpRequest();

    elems = document.querySelectorAll('ul li a'); // adds listener
    [].forEach.call(elems, function (el) {
        el.addEventListener('click', handle_M_B_S, false);
    });
    submitVal("mem", 0);
}
