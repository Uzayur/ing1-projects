let text_var = document.getElementById("textBox");
let list = document.getElementById("todoList");

addButton.addEventListener("click", add_item);

function add_item() {
    if (text_var.value.length == 0)
        return;

    let new_b = document.createElement("button");
    var label = document.createTextNode("Delete");
    new_b.appendChild(label);
    new_b.addEventListener("click", delete_item);

    var list_item = document.createElement("li");
    list_item.className = "todoItem";

    var item = document.createElement("span");
    var textNode = document.createTextNode(text_var.value);
    item.appendChild(textNode);
    item.className = "todoText";

    list_item.appendChild(item);
    list_item.appendChild(new_b);

    list.appendChild(list_item);

    text_var.value = "";
}

function delete_item() {
    this.parentElement.remove();
}
