const BackToTopButton = document.getElementById('BackToTop');
const ReturnToProjectsButton = document.getElementById('ReturnToProjects');

BackToTopButton.addEventListener('click', function () {
  document.body.scrollTop = 0;
  document.documentElement.scrollTop = 0;
});

ReturnToProjectsButton.addEventListener('click', function () {
  window.location.href = "/projects/";
});
