let votes = {
    "Mr. Bigglesworth" : 0,
    "Mittens" : 0,
    "Snowball" : 0,
    "Dave" : 0,
    "Valentine" : 0,
    "Miss Tinkles" : 0,
    "Claws" : 0
}


function main() {
    voteform.onsubmit = event => {
        if (nominee.value != "") {
            selection = nominee.value;
            loading();
            setTimeout(() => {
                displayResult(generateVotes(selection), selection);
            }, 2500);

        }

        return false;
    }

    function loading() {
        $("#app-container").empty();
        let h = document.createElement("h5");
        h.style = "text-align: center; font-weight: normal";
        h.innerHTML = "Polls are now closed.";

        let newdiv = document.createElement("div");
        newdiv.className = "text-center m-5";

        let spinnerdiv = document.createElement("div");
        spinnerdiv.className = "spinner-border text-light";
        spinnerdiv.setAttribute("role", "status");

        let loading = document.createElement("h6");
        loading.innerHTML = "Calculating Results...";

        newdiv.append(spinnerdiv, loading);
        $("#app-container").append(h, newdiv);
    }

    function generateVotes(selection) {
        for (cat in votes) {
            votes[cat] = Math.floor(Math.random() * (5000 - 2500 + 1)) + 2500;
        }
        votes[selection] *= 2;

        let total = 0;
        for (cat in votes) {
            total += votes[cat];
        }

        return total;
    }

    function displayResult(total, selection) {
        chartdiv = document.createElement("div");
        chartdiv.className = "container-fluid";
        chartdiv.id = "chart-container";

        for (cat in votes) {
            let percent = Math.floor((100 * votes[cat]) / 10000);

            let bar = document.createElementNS('http://www.w3.org/2000/svg','svg');

            let bg = document.createElementNS("http://www.w3.org/2000/svg", "rect");
            bg.setAttribute("class","bar-bg");

            let barinner = document.createElementNS('http://www.w3.org/2000/svg','svg');
            barinner.setAttribute("width", `${percent}%`);

            let fill = document.createElementNS("http://www.w3.org/2000/svg", "rect");
            fill.setAttribute("class","bar-fill");

            if (cat == selection) {
                fill.setAttribute("id", "winner");
            }

            barinner.append(fill);

            let text = document.createElementNS("http://www.w3.org/2000/svg", "text");
            text.setAttribute("x", "5%");
            text.setAttribute("y", "70%");
            text.innerHTML = cat;

            bar.append(bg, barinner, text);

            chartdiv.append(bar);
        }

        $("#app-container").empty();
        $("#app-container").append(chartdiv);

        setTimeout(() => {
                if (selection == "Dave") {
                    windiv = document.createElement("div");
                    windiv.className = "text-center";
                    winh1 = document.createElement("h1");
                    winh1.innerHTML = `${selection} wins!`;
                    winh4 = document.createElement("h4");
                    winh4.innerHTML = "We did it! Now with our secret agent in control, cats don't stand a chance. Let's get to work.";
                    winimg = document.createElement("img");
                    winimg.src = "./imgs/swatraid.gif";

                    windiv.append(winh1, winh4, winimg);
                    $("#app-container").append(windiv);
                }
                else if (selection == "Claws") {
                    windiv = document.createElement("div");
                    windiv.className = "text-center";
                    winh1 = document.createElement("h1");
                    winh1.innerHTML = `${selection} wins!`;
                    winh4 = document.createElement("h4");
                    winh4.innerHTML = "Something's fishy here ... wait, <a href='https://www.youtube.com/watch?v=tV5wmDhzgY8&t=5s' target='_blank'>do you hear that?</a>";
                    winimg = document.createElement("img");
                    winimg.src = "./imgs/crabparty.jpg";

                    windiv.append(winh1, winh4, winimg);
                    $("#app-container").append(windiv);
                }
                else {
                    windiv = document.createElement("div");
                    windiv.className = "text-center";
                    winh1 = document.createElement("h1");
                    winh1.innerHTML = `${selection} wins!`;
                    winh4 = document.createElement("h4");
                    winh4.innerHTML = "Looks like another year of tyranny for us all. Better luck next time.";
                    winimg = document.createElement("img");
                    winimg.src = "./imgs/catroyalty.jpg";

                    windiv.append(winh1, winh4, winimg);
                    $("#app-container").append(windiv);
                }

        }, 3100);
    }
}

document.addEventListener("DOMContentLoaded", main);