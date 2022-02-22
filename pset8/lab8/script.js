(function () {
    let possibleAnswers = document.querySelectorAll('button');
    let firstQuestion = document.querySelector('.section#first');
    for (let i = 0; i < possibleAnswers.length; i++) {
        possibleAnswers[i].correct = false;
        possibleAnswers[i].addEventListener('click', function (e) {
            let lastAnswer = document.querySelector('.section#first p')
            reset(possibleAnswers, firstQuestion, lastAnswer);
            checkMultipleAnswer(e.target);
        });
    }
    possibleAnswers[3].correct = true;

    let form = document.querySelector('form');
    let secondQuestion = document.querySelector('.section#second');
    form.addEventListener('submit', function (e) {
        let lastAnswer = document.querySelector('.section#second p');
        e.preventDefault(); //Not send the form when press <Enter>
        reset(e.target, secondQuestion, lastAnswer);
        checkTextAnswer(form[0]);
    });

    function checkMultipleAnswer(option) {
        let message = {
            element: document.createElement('p'),
            text: option.correct ? 'Correct!' : 'Incorrect',
            cssClass: option.correct ? 'correct' : 'incorrect'
        };

        let output = firstQuestion.appendChild(message.element);
        output.innerText = message.text;
        option.classList.add(message.cssClass);

    }

    function checkTextAnswer(answer) {
        const TEXT_ANSWER = 'ALBERT EINSTEIN';

        let message = {
            element: document.createElement('p'),
            text: answer.value.toUpperCase() == TEXT_ANSWER ? 'Correct!' : 'Incorrect',
            cssClass: answer.value.toUpperCase() == TEXT_ANSWER ? 'correct' : 'incorrect'
        };

        let output = secondQuestion.appendChild(message.element);
        output.innerText = message.text;
        answer.classList.add(message.cssClass);
    }

    function reset (obj, father, lastAnswer) {
        if (lastAnswer) {
            father.removeChild(lastAnswer);
        }

        for (let i = 0; i < obj.length; i++) {
            obj[i].classList.remove('correct', 'incorrect');
        }
    }
}());