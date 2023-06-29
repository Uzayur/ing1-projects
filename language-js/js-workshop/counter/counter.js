let count_var = document.getElementById("count");
let count = document.getElementById("count").innerHTML;

plus.addEventListener("click", plus_action);
minus.addEventListener("click", minus_action);

function plus_action() { count++; count_var.innerHTML = count}
function minus_action() { count--; count_var.innerHTML = count}
