const cats = {
    "United States" : [
        {
            "id": "0",
            "url": "./imgs/americanshorthair.jpg",
            "name": "American Shorthair",
            "description": "A descendent of the cats that came over with the Mayflower colonists."
        },
        {
            "id": "1",
            "url": "./imgs/mainecoon.jpg",
            "name": "Maine Coon",
            "description": "The offical cat of Maine, this gentle giant is one of the largest cat breeds."

        },
        {
            "id": "2",
            "url": "./imgs/ragdoll.jpg",
            "name": "Ragdoll",
            "description": "Named for their tendency to go completely limp when picked up."

        }],

    "Canada" : [
        {
            "id": "0",
            "url": "./imgs/sphynx.jpg",
            "name": "Sphynx",
            "description": "This breed originated in Toronto, Ontario. The first Sphynx cat was named Prune."
        },
        {
            "id": "1",
            "url": "./imgs/exoticfold.jpg",
            "name": "Exotic Fold (Foldex)",
            "description": "Similar to a Scottish Fold but bred to be a little less fold-y."
        }],

    "South America" : [
        {
            "id": "0",
            "url": "./imgs/safari.jpg",
            "name": "Safari Cat",
            "description": "This is a rare hybrid breed that came from mixing wild and domestic cats."
        },
        {
            "id": "1",
            "url": "./imgs/jaguar.jpg",
            "name": "Jaguar",
            "description": "South America is mostly full of cats that will kill you. Pls do not pet."
        }],

    "United Kingdom" : [
        {
            "id": "0",
            "url": "./imgs/britishshorthair.jpg",
            "name": "British Shorthair",
            "description": "It has short hair and it's from Britain."
        },
        {
            "id": "1",
            "url": "./imgs/scottishfold.jpg",
            "name": "Scottish Fold",
            "description": "Voted 'Saddest Looking Cat' since 1966."
        },
        {
            "id": "2",
            "url": "./imgs/cornishrex.jpg",
            "name": "Cornish Rex",
            "description": "This breed doesn't have an outer coat but only a soft, down-like undercoat."
        }],

    "Russia" : [
        {
            "id": "0",
            "url": "./imgs/russianblue.jpg",
            "name": "Russian Blue",
            "description": "Named for their silver coats which can sometimes look blueish-grey."
        },
        {
            "id": "1",
            "url": "./imgs/siberian.jpg",
            "name": "Siberian",
            "description": "Certified floofballs with thick coats to survive winter."
        }],

    "China" : [
        {
            "id": "0",
            "url": "./imgs/persian.jpg",
            "name": "Persian",
            "description": "One of the most popular cat breeds out there. No idea why though, I mean look at it."
        },
        {
            "id": "1",
            "url": "./imgs/siamese.jpg",
            "name": "Siamese",
            "description": "Remember the Lady and the Tramp? Those cats were dicks."
        },
        {
            "id": "2",
            "url": "./imgs/bengal.jpg",
            "name": "Bengal",
            "description": "This breed looks more like an exotic jungle cat than a house pet. Unlike most cats they enjoy water."
        }],

    "Africa" : [
        {
            "id": "0",
            "url": "./imgs/egyptianmau.jpg",
            "name": "Egyptian Mau",
            "description": "One of the few naturally spotted breeds of domesticated cat."
        },
        {
            "id": "1",
            "url": "./imgs/abyssinian.jpg",
            "name": "Abyssinian",
            "description": "One of the most ancient of all cat breeds, it's been found mummified in Egyptian tombs."
        }],

    "Australia" : [
        {
            "id": "0",
            "url": "./imgs/australianmist.jpg",
            "name": "Australian Mist",
            "description": "A cross between the Abyssinian, the Burmese and the Australian Tabby."
        },
        {
            "id": "1",
            "url": "./imgs/nativecat.jpg",
            "name": "Quoll (Native Cat)",
            "description": "This is what came up when I Googled 'Native Cat Australia' so here you go."
        }],
}

function main() {

    //Add listeners for location selectors
    let locations = document.querySelectorAll('.mapMarker');
    locations.forEach(element => element.addEventListener('click', displayCats));

    locations = document.querySelectorAll('.mapbutton');
    locations.forEach(element => element.addEventListener('click', displayCats));

    //Enable tooltips
    $('[data-toggle="tooltip"]').tooltip({trigger : 'hover'});

    //When location is clicked, loop through the cat objects for that location
    //Create elements and add them to the document
    function displayCats(event) {
        $("#carouselItems").empty();
        $("#carouselIndicators").empty();
        modalTitle.innerHTML = event.target.value;

        cats[event.target.value].forEach(cat => {

            let catdiv = document.createElement("div");
            catdiv.className = "carousel-item";
            catdiv.id = `item${cat["id"]}`;

            let catimg = document.createElement("img");
            catimg.src = cat["url"];
            catimg.className = "d-block w-100 carousel-img";

            let captiondiv = document.createElement("div");
            captiondiv.className = "carousel-caption d-none d-md-block";

            let txt = document.createElement("h4");
            txt.innerHTML = cat["name"];
            captiondiv.append(txt);
            txt = document.createElement("p");
            txt.innerHTML = cat["description"];
            captiondiv.append(txt);

            catdiv.append(catimg, captiondiv);

            carouselItems.append(catdiv);
        })

        item0.className = "carousel-item active";

        return false;
    }
}

document.addEventListener("DOMContentLoaded", main);