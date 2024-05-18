console.log("Hellow, WORLD!!");

//reverse the color of the image when you hover over it.
const image = document.getElementById('flowers');

const org = 'flowers3.png';
const rev = 'rflowers3.png';

image.addEventListener('mouseover', () => {
    image.src = rev;
});

image.addEventListener('mouseout', () => {
    image.src = org;
});