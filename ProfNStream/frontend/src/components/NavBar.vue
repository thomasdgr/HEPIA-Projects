<template>
  <div class="top_navbar">
    <div class="class_information">
      <p class="Title">Introduction à l'électrodynamique</p>
      <p class="par">par</p>
      <p class="Author">Mr.Pump</p>
    </div>
    <div class="user_information">
      <p class="Timer"></p>
      <Icon class="myCoinIcon" icon="fa-solid:coins" />
      <p id="credit"></p>
      <p id="name"></p>
      <Icon class="myCoinIcon" icon="fa-solid:profil" />
    </div>
  </div>
</template>
<script>
import { Icon } from "@iconify/vue2";
import swal from "sweetalert2";
import Vue from "vue";

export default {
  components: {
    Icon,
  },
  data() {
    return {
      timerInterval: null,
      time: 0,
      credits: 42,
      myHeader: new Headers({
        "Access-Control-Allow-Origin":
          "http://" + Vue.prototype.$BACKENDURL + ":8080",
        Accept: "application/json",
        "Content-Type": "application/json",
      }),
    };
  },
  beforeMount() {
    console.log("RoomID ", Vue.prototype.$roomID);
    this.getTime(Vue.prototype.$userID, Vue.prototype.$roomID).then((a) => {
      this.time = Math.floor(Math.max(a, 0) / 1000);
      console.log("getTime Res:", this.time, "vs", a);
      if (this.time > 0) {
        this.timerInterval = window.setInterval(this.updateClock, 1000);
      } else {
        this.handleTimeOut();
      }
    });
  },
  methods: {
    handleTimeOut(){
       this.checkIfUserPaid(Vue.prototype.$userID, Vue.prototype.$roomID).then((res) => {
        console.log("HEYHEYHEY");
         if (!res) {
            console.log("UPUPUPUPUP");
            clearInterval(this.timerInterval);
            swal
              .fire({
                title: "Periode gratuite terminée",
                text: "Souhaitez-vous utiliser vos crédits pour continuer le cours ?",
                icon: "warning",
                showDenyButton: true,
                showCancelButton: false,
                confirmButtonColor: "#993bbb",
                confirmButtonText: "Continuer",
                denyButtonText: `Quitter`,
                allowOutsideClick: false,
              })
              .then((result) => {
                if (result.isConfirmed) {
                  this.debitUser(Vue.prototype.$userID, Vue.prototype.$roomID).then((res) => {
                    this.credits = res;
                    if (this.credits >= 0) {
                      // tester si le user a assez de crédit et si c'est le cas, on le débit
                      swal.fire({
                        icon: "success",
                        title: "Merci",
                        text: "Vous avez été débité de 1 crédit",
                        showConfirmButton: false,
                        allowOutsideClick: false,
                        timer: 2000,
                      });
                      document.getElementById("credit").textContent = this.credits;
                    } else {
                      swal.fire({
                        icon: "error",
                        title: "Echec",
                        text: "Vous n'avez pas assez de crédit pour continuer le cours",
                        showConfirmButton: false,
                        allowOutsideClick: false,
                        timer: 2000,
                      });
                      // rediriger vers la page d'accueil
                    }
                    this.$root.$emit("clearSourceEvent");
                    this.$router.push("acceuil");
                  });
                } else if (result.isDenied) {
                  // rediriger vers la page d'accueil
                  this.$root.$emit("clearSourceEvent");
                  this.$router.push("acceuil");
                }
              });
            //location.reload();
          }
        });
    },
    userHasCredit(userID) {
      console.log(userID);
      return false;
    },
    getUserCredits(userID) {
      return fetch("http://" + Vue.prototype.$BACKENDURL + ":8080/payment/credits/" + userID, {
        method: "get",
        headers: this.myHeader,
      }).then((res) => {
        return res.json().then((o) => o["credits"]);
      });
    },
    updateClock() {
      document.getElementById("credit").textContent = this.credits;
      document.getElementById("name").textContent = Vue.prototype.$userID;
      this.time = Math.max(0, this.time - 1);
      document.getElementsByClassName("Timer")[0].innerHTML = this.toHHMMSS(
        this.time
      );
    },
    checkIfUserPaid(userID, streamID) {
      return fetch(
        "http://" + Vue.prototype.$BACKENDURL + ":8080/payment/check/" + streamID + "/" + userID,
        { method: "get", headers: this.myHeader }
      ).then((res) => {
        return res.json().then((o) => o["credits"]);
      });
    },
    // EXEMPLE checkIfUserIsProf(11).then(res => console.log("--> " + res));
    checkIfUserIsProf(userID) {
      return fetch("http://" + Vue.prototype.$BACKENDURL + ":8080/credential/" + userID, {
        method: "get",
        headers: this.myHeader,
      }).then((res) => {
        return res.json().then((o) => o["credential"]);
      });
    },
    banUser(userID, streamID) {
      return fetch(
        "http://" + Vue.prototype.$BACKENDURL + ":8080/banned/add/" + streamID + "/" + userID,
        { method: "get", headers: this.myHeader }
      );
    },
    checkIfUserBanned(userID, streamID) {
      return fetch(
        "http://" + Vue.prototype.$BACKENDURL + ":8080/banned/check/" + streamID + "/" + userID,
        { method: "get", headers: this.myHeader }
      ).then((res) => {
        return res.json().then((o) => o["result"]);
      });
    },
    debitUser(userID, streamID) {
      return fetch(
        "http://" +
          Vue.prototype.$BACKENDURL +
          ":8080/payment/" +
          streamID +
          "/" +
          userID,
        {
          method: "get",
          headers: this.myHeader,
        }
      ).then((res) => {
        return res.json().then((o) => o["credits"]);
      });
    },
    getTime(userID, streamID) {
      return fetch(
        "http://" +
          Vue.prototype.$BACKENDURL +
          ":8080/timer/" +
          streamID +
          "/" +
          userID,
        {
          method: "get",
          headers: this.myHeader,
        }
      ).then((res) => {
        return res.json().then((o) => o["timer"]);
      });
    },
    toHHMMSS(time) {
      let sec_num = time; // don't forget the second param
      let minutes = Math.floor(sec_num / 60);
      let seconds = time - minutes * 60;

      if (minutes < 10) {
        minutes = "0" + minutes;
      }
      if (seconds < 10) {
        seconds = "0" + seconds;
      }
      return minutes + ":" + seconds;
    },
  },
};
</script>

<style>
.swal2-title,
.swal2-text {
  font-family: Courier New, monospace;
}

.top_navbar {
  overflow: hidden;
  background-color: #6f30a0;
  display: flex;
  justify-content: space-between;
  position: fixed;
  top: 0; /* Position the navbar at the top of the page */
  width: 100%; /* Full width */
  z-index: 1;
}

.class_information {
  display: flex;
  color: white;
}
.class_information p {
  margin: 0px 0px 0px 0px;
  padding: 1vh 0vh 1vh 1vh;
  margin-top: auto;
  opacity: 0.5;
}

.class_information .Title {
  font-weight: bold;
  text-decoration: underline;
  font-size: 4vh;
  opacity: 1;
}

.class_information .Author {
  text-decoration: underline;
  font-size: 2vh;
}

p {
  font-size: 2vh;
}

.user_information {
  display: flex;
  color: white;
  margin-right: 5vh;
}

.user_information .Timer {
  color: #12ff00;
  background-color: #993bbb;
  border-style: solid;
  border-radius: 2vh;
  border-color: #12ff00;
  padding: 1vh 2vh 0vh 2vh;
  margin: auto;
  font-size: 3vh;
}
.myCoinIcon {
  margin: auto;
  padding: 1vh 1vh 1vh 2vh;
  font-size: 3vh;
}

.myProfilIcon {
  margin: auto;
  padding: 1vh 1vh 1vh 2vh;
  font-size: 3vh;
}

.user_information #credit {
  margin: auto;
  padding: 1vh 2vh 0vh 1vh;
  font-size: 3vh;
}

@media only screen and (max-width: 810px) {
  .top_navbar {
    display: inline-block;
  }
  .class_information .Title {
    font-size: 2vh;
  }
  .class_information .par {
    font-size: 1vh;
  }
  .class_information .Author {
    font-size: 1vh;
  }
  .user_information .Timer {
    margin: 0vh 1vh 0vh 8vh;
    font-size: 2vh;
  }
  .user_information .Credit {
    padding: 0vh 0vh 0vh 0vh;
    margin: 0vh 0vh 0vh 1vh;
    font-size: 3vh;
  }
  .myCoinIcon {
    margin: 0vh 0vh 0vh 12vh;
    padding: 0vh 0vh 0vh 0vh;
    font-size: 3vh;
  }
  .myProfilIcon {
    margin: 0vh 0vh 0vh 2vh;
    padding: 0vh 0vh 0vh 0vh;
    font-size: 3vh;
  }

  .user_information #name {
    margin: auto;
    padding: 1vh 0vh 0vh 1vh;
    font-size: 3vh;
  }
}
</style>