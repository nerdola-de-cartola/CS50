(function () {
    const MY_EMAIL = 'nerdola.cartola@gmail.com';
    const CLIENTS = [];
    let form = document.querySelector('form');
    let address = form[0];
    let subject = form[1];
    let body = form[2];

    form.addEventListener('submit', function (e) {
        e.preventDefault();
        saveClientEmail(address);
        sendEmail(subject.value, body.value);
    });

    function sendEmail(subject, body) {
        document.location.href = 'mailto:'+
        encodeURIComponent(MY_EMAIL) + '?subject=' +
        encodeURIComponent(subject) + '&body=' +
        encodeURIComponent(body);
    }

    //Saving data from user to save latter in SqLite
    function saveClientEmail(address) {
        let client = {
            address: address.value,
            time: new Date()
        };

        CLIENTS.push(client);
    }
}());