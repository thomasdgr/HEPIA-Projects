<template>
  <div>
    <img
      :src="imageSource"
      width="40"
      height="120"
      :style="CollapseMovmChat"
      class="Collapsebtn"
      v-on:click="collapse"
    />
    <collapse-transition dimension="width" :duration="0">
      <div class="ComponentChat" v-show="isOpen">
        <div class="Messages"></div>
        <div class="submitMessage">
          <textarea
            id="message"
            type="text"
            @keypress.enter="sendMessage()"
            v-model="text"
            placeholder="Écrivez votre message..."
          />
          <img
            src="../assets/btn_send.png"
            width="40"
            height="40"
            class="btn_send"
            v-on:click="sendMessage()"
          />
          <input type="checkbox" id="question" name="subscribe" />
          <label for="subscribeNews">question</label>
        </div>
        <label>{{ checked }}</label>
      </div>
    </collapse-transition>
  </div>
</template>

<script>
import { CollapseTransition } from "@ivanv/vue-collapse-transition";
import { defineComponent } from "@vue/composition-api";
import Vue from "vue";
import swal from "sweetalert2";

function lol() {
  let userID = Vue.prototype.$userID;
  let streamID = Vue.prototype.$roomID;
  console.log("hello");

  console.log("current userID = " + userID);
  var newProfUserID = 11;
  console.log("new userID = " + newProfUserID);

  var userToBan = 2;
  console.log("new userID to ban = " + userToBan);

  var newStreamID = 0;
  console.log("current streamID = " + streamID);
  console.log("new streamID = " + newStreamID);

  this.checkIfUserIsProf(newProfUserID).then((res) => {
    if (res) {
      swal
        .fire({
          position: "center-end",
          target: document.getElementsByClassName("Messages"),
          width: document.getElementsByClassName("Messages")[0].clientWidth,
          text: "Que souhaitez-vous faire ?",
          showDenyButton: true,
          showCancelButton: true,
          confirmButtonColor: "#ff0000",
          denyButtonColor: "#993bbb",
          confirmButtonText: "Bannir l'utilisateur",
          denyButtonText: `Supprimer le message`,
          allowOutsideClick: false,
        })
        .then((result) => {
          if (result.isConfirmed) {
            this.banUser(newStreamID, userToBan).then((res) => {
              if (res == 200) {
                swal.fire({
                  position: "center-end",
                  target: document.getElementsByClassName("Messages"),
                  width:
                    document.getElementsByClassName("Messages")[0].clientWidth,
                  text: "Utilisateur banni!",
                });
              }
            });
          } else if (result.isDenied) {
            swal.fire({
              position: "center-end",
              target: document.getElementsByClassName("Messages"),
              width: document.getElementsByClassName("Messages")[0].clientWidth,
              text: "Message supprimé",
            });
          }
        });
    }
  });
}
window.lol = lol;
export default defineComponent({
  components: {
    mixins: [Vue, Vue.prototype.$io, CollapseTransition],
    CollapseTransition,
  },
  data() {
    return {
      myHeader: new Headers({
        "Access-Control-Allow-Origin":
          "http://" + Vue.prototype.$BACKENDURL + ":8080",
        Accept: "application/json",
        "Content-Type": "application/json",
      }),
      socket: null,
      isOpen: true,
      imageSource: require("@/assets/collapse.png"),
      winWidth: 0,
    };
  },
  beforeMount() {
    this.initSockets();
    console.log("Hey initialized sockets!");
  },
  mounted() {
    this.winWidth = window.innerWidth;
    var test;
    window.onresize = () => {
      clearTimeout(test);
      test = setTimeout(this.resizeWidth, 1);
    };
  },
  destroyed() {
    window.onresize = null;
  },
  methods: {
    banUser(streamID, userID) {
      return fetch(
        "http://localhost:8080/banned/add/" + streamID,
        +"/" + userID,
        { method: "get", headers: this.myHeader }
      ).then((res) => {
        return res.status;
      });
    },
    checkIfUserIsProf(userID) {
      return fetch("http://localhost:8080/credential/" + userID, {
        method: "get",
        headers: this.myHeader,
      }).then((res) => {
        return res.json().then((o) => o["credential"]);
      });
    },
    initSockets() {
      this.socket = Vue.prototype.$io(
        "http://" + Vue.prototype.$BACKENDURL + ":3000",
        {
          origin: "*",
          extraHeaders: {
            "my-custom-header": "abcd",
          },
        }
      );
      this.socket.on("connect", () => {});
      this.socket.emit("init", {
        roomID: Vue.prototype.$roomID,
        userID: Vue.prototype.$userID,
      });
      this.socket.on("recieve message", (args) => {
        if (args["userID"] == Vue.prototype.$userID) {
          return;
        }
        this.pushMessage(args);
      });
    },
    pushMessage(msg) {
      //Probably need a whitespace filter
      console.log(msg);
      let color = "";
      if (msg["question"] == 1) {
        color = "color:red;";
      }
      document.getElementsByClassName("Messages")[0].innerHTML =
        '<div> \
      <button onclick="lol()" style="  padding: 0;border: none;background: none;"> \
        <p style="font-weight:bolder;' +
        color +
        '">' +
        msg["userID"] +
        ": " +
        '</p> \
        <p style="' +
        color +
        'word-wrap:break-word;">' +
        msg["msg"] +
        "</p> \
      </button> \
      </div>" +
        document.getElementsByClassName("Messages")[0].innerHTML;
    },
    sendMessage() {
      var msg = document.getElementById("message").value;
      document.getElementById("message").value = "";

      //Probably need a better whitespace filter
      if (msg.replace(" \n\t\r", "") != "") {
        let message = {
          msg: msg,
          roomID: Vue.prototype.$roomID,
          userID: Vue.prototype.$userID,
          question: document.getElementById("question").checked,
        };
        this.socket.emit("chat message", message);
        this.pushMessage(message);
      }
    },
    collapse: function () {
      this.isOpen = !this.isOpen;
      if (this.isOpen) {
        this.imageSource = require("@/assets/collapse.png");
      } else {
        this.imageSource = require("@/assets/expand.png");
      }
      this.$emit("collapse", this.isOpen);
    },
    resizeWidth() {
      this.winWidth = window.innerWidth;
    },
  },
  computed: {
    CollapseMovmChat() {
      if (this.isOpen) {
        if (this.winWidth < 810) {
          return {
            top: "28%",
            right: "50%",
          };
        } else {
          return {
            top: "85%",
            right: "20.2%",
          };
        }
      } else {
        if (this.winWidth < 810) {
          return {
            top: "94%",
            right: "50%",
          };
        } else {
          return {
            top: "85%",
            right: "0%",
          };
        }
      }
    },
  },
});
</script>

<style scoped>
.Collapsebtn {
  display: flex;
  flex-direction: column;
  top: 85%;
  position: fixed;
  height: 10%;
  width: 2%;
  z-index: 1;
}

.ComponentChat {
  background-color: #fff;
  width: 20.2%;
  display: flex;
  flex-direction: column;
  position: fixed;
  right: 0;
  top: 7%;
  height: 100%;
  border: 3 solid #6f30a0;
  font-size: 2vh;
  z-index: 1;
}

.Messages {
  height: 80%;
  padding-left: 5px;
  overflow: auto;
  display: flex;
  flex-direction: column-reverse;
}

.submitMessage {
  display: inline-block;
  flex-direction: column;
  height: 20%;
  background-color: #e0e0e0;
  padding-left: 1vh;
  height: 10vh;
  border-radius: 2vh;
  margin: 1vh;
}

.submitMessage textarea {
  background-color: #e0e0e0;
  border-radius: 2%;
  resize: none;
  font-family: "Ropa Sans", sans-serif;
  border-style: none;
  border-color: Transparent;
  overflow: auto;
  height: 3vh;
  width: 30vh;
  font-size: 2vh;

  border: none;
  overflow: auto;
  outline: none;
  -webkit-box-shadow: none;
  -moz-box-shadow: none;
  box-shadow: none;

  resize: none;
}

.submitMessage label {
  font-family: "Ropa Sans", sans-serif;
  color: #696969;
}

.btn_send {
  padding-top: 2vh;
  padding-left: 3vh;
  width: 4vh;
  height: 4vh;
}

#question {
  width: 2vh;
}

.kek {
  padding: 0;
  border: none;
  background: none;
}

@media only screen and (max-width: 810px) {
  .ComponentChat {
    top: 35%;
    width: 100%;
  }
  .Collapsebtn {
    transform: rotate(90deg);
    width: 7%;
  }
  .Messages {
    height: 54%;
  }
  .btn_send {
    padding-left: 6vh;
  }
}
</style>