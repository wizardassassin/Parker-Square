const squareButton = document.getElementById("submit-square");
const autoButton = document.getElementById("submit-automatic");
const autoCell = document.getElementById("automatic-input");
const squareCells = document
    .getElementById("square-grid")
    .querySelectorAll("input.square-input");
const outputDiv = document.getElementById("output");

autoButton.addEventListener("click", (event) => {
    const value = autoCell.value;
    console.log(value);
});

squareButton.addEventListener("click", (event) => {
    const data = Array.from(squareCells, (x) => BigInt(x.value));
    while (outputDiv.firstChild) {
        outputDiv.removeChild(outputDiv.firstChild);
    }
    console.log(data);
    const combinations = [
        [0, 1, 2, "Row 1"],
        [3, 4, 5, "Row 2"],
        [6, 7, 8, "Row 3"],
        [0, 3, 6, "Col 1"],
        [1, 4, 7, "Col 2"],
        [2, 5, 8, "Col 3"],
        [0, 4, 8, "Dia 1"],
        [2, 4, 6, "Dia 2"],
    ];
    for (const combo of combinations) {
        const div = document.createElement("div");
        div.textContent = `${combo[3]}: ${
            data[combo[0]] ** 2n + data[combo[1]] ** 2n + data[combo[2]] ** 2n
        }`;
        outputDiv.appendChild(div);
    }
});
