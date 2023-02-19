const modal = document.querySelector(".modal");
const overlay = document.querySelector(".overlay");
const btnCloseModal = document.querySelector(".close-modal");
const btnOpenModal = document.querySelector(".disclaimer");
const openModal = () => {
  modal.classList.remove("hidden");
  overlay.classList.remove("hidden");
};
const closeModal = () => {
  modal.classList.add("hidden");
  overlay.classList.add("hidden");
};
let lastThirdOfTheNightTimeStart = document.getElementById("third");
let midnightStart = document.getElementById("midnight");
let difference = 0;
let thirdOfTheDifference = 0;
let halfOfTheDifference = 0;
let lastThirdOfTheNight = 0;
let midnight = 0;

let calculateTimes = () => {
  let magrib = document.getElementById("magrib").value;
  let fajr = document.getElementById("fajr").value;
  if (magrib == "" || fajr == "") {
    window.alert(
      "Value cannot be zero. Try again."
    );
  } else {
    let hoursMagrib=parseInt(document.getElementById("magrib").value.split(/[:]/));
    let hoursFajr=parseInt(document.getElementById("fajr").value.split(/[:]/));
    let subtract=hoursFajr-hoursMagrib;

     // Example sunset 20:00, dawn 04:00
     if(subtract<0){
      magrib = dayjs(`2000-01-01 ${document.getElementById("magrib").value}`);
    fajr = dayjs(`2000-01-02 ${document.getElementById("fajr").value}`);
     }
      // Example sunset 00:00, dawn 02:00
     else{
      magrib = dayjs(`2000-01-01 ${document.getElementById("magrib").value}`);
    fajr = dayjs(`2000-01-01 ${document.getElementById("fajr").value}`);
     }
    
   difference = fajr.diff(magrib);
   if(difference===0)
   window.alert("Values cannot be the same! Enter correct values.");
   if(difference){
    thirdOfTheDifference = difference / 3;
    halfOfTheDifference = difference / 2;
    lastThirdOfTheNight = fajr.subtract(thirdOfTheDifference, "milliseconds").format("HH:mm");
    midnight = fajr.subtract(halfOfTheDifference, "milliseconds").format("HH:mm");
    lastThirdOfTheNightTimeStart.innerHTML = lastThirdOfTheNight;
    lastThirdOfTheNightTimeStart.style.visibility = "visible";
    midnightStart.innerHTML = midnight;
    midnightStart.style.visibility = "visible";
    document.getElementById("disclaimer").style.visibility = "visible";
    document.querySelector(".userthird").innerHTML = lastThirdOfTheNight;
    document.querySelector(".usermidnight").innerHTML = midnight;
   }
    
  }
};

document
  .querySelector(".calculate")
  .addEventListener("click", calculateTimes);

btnOpenModal.addEventListener("click", openModal);

btnCloseModal.addEventListener("click", closeModal);
overlay.addEventListener("click", closeModal);

document.addEventListener("keydown", e => {
  if (e.key === "Escape" && !modal.classList.contains("hidden")) {
    closeModal();
  };
});
