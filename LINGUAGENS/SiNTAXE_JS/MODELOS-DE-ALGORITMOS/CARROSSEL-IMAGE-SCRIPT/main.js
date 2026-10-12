


document.addEventListener('DOMContentLoaded',  () => {
    const items = document.querySelectorAll('.carrossel-item');
    const prevBtn = document.getElementById('anterior-btn');
    const nextBtn = document.getElementById('proximo-btn');
    let currentIndex = 0;

    // atualizar a imagem ativa
    function updateCarousel() {
            items.forEach((item, index) => {
                item.classList.toggle('active', index === currentIndex);

            });
    }
    //   proxima imagem
    nextBtn.addEventListener('click',  () => {
         currentIndex = (currentIndex + 1)  % items.length;      // volta no início
         updateCarousel();
    });
    //imagem anterior
    prevBtn.addEventListener('click', () => {
        currentIndex = (currentIndex - 1 + items.length) % items.length; 
        updateCarousel();
    });




    //chama o carrossel
    updateCarousel();
});