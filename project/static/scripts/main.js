import Modal from './modal.js';
const modal = Modal();

// Array of buttons
const checkButtons = document.querySelectorAll('.actions a.check');
const deleteButtons = document.querySelectorAll('.actions a.delete');

// HTML objects
const modal_title = document.querySelector('.modal h2');
const modal_description = document.querySelector('.modal p');
const modal_button = document.querySelector('.modal button');

// Add event to mark question as read
checkButtons.forEach(button => {
    button.addEventListener('click', (event) => handleClick(event, true));
});

// Add event to delete questions
deleteButtons.forEach(button => {
    button.addEventListener('click', (event) => handleClick(event, false) );
});

function handleClick (event, check) {
    event.preventDefault();

    const text = check ? 'Mark as read' : 'Delete';
    const slug = check ? 'check' : 'delete';

    const room_id = document.querySelector('#room-id').dataset.id;
    const question_id = event.target.dataset.id;
    const form = document.querySelector('.modal form');

    // Insert HTML attribute "action"
    form.setAttribute('action', `/room/${room_id}/question/${question_id}/${slug}`);

    modal_title.innerHTML = text;
    modal_description.innerHTML = `Are you sure to ${text.toLocaleLowerCase()} this question ?`;
    modal_button.innerHTML = `Yes, ${text.toLocaleLowerCase()}`;
    check ? modal_button.classList.remove('red') : modal_button.classList.add('red');

    modal.open();
}