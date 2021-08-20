const overlay = {
    "cat": "Gigacat: has science gone too far?",
    "fish": "You thought the water was safe? Think again.",
    "human": "Jesus weeps.",
    "cow": '"Mooo-eow."',
    "shark": "*Jaws Theme*",
    "dinosaur": "Life finds a way.",
    "duck": "DUBAR: Ducked up beyond all recognition.",
    "mouse": "tfw you play cat and mouse with yourself"
}

function main() {
                catMixer.onsubmit = event => {
                    if (sample.value != "") {
                        image.src = `./imgs/${sample.value}_cat.jpg`;
                        placeholderTxt.hidden = true;
                        image.hidden = false;
                        overlayTxt.hidden = false;
                        overlayTxt.innerHTML = overlay[sample.value]
                        return false;
                    }
                    else {
                        image.hidden = true;
                        overlayTxt.hidden = true;
                        placeholderTxt.hidden = false;
                        return false;
                    }
                }
            }

document.addEventListener("DOMContentLoaded", main);