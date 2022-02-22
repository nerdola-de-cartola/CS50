// Export javascript function to use it in other js files
export default function Modal() {

    const modal_wrapper = document.querySelector('.modal_wrapper');
    const cancel_button = document.querySelector('.button.cancel');

    cancel_button.addEventListener('click', close);

    // Show modal
    function open() {
        modal_wrapper.classList.add('active');
    }

    // Hide modal
    function close() {
        modal_wrapper.classList.remove('active');
    }

    return {
        open,
        close
    };
}