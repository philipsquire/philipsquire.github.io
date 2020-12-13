var BackToTopButton = document.getElementById("BackToTop");

BackToTopButton.addEventListener('click', function () {
    document.body.scrollTop = 0;
    document.documentElement.scrollTop = 0;
  });