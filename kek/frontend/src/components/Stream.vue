<template>
  <div>
    <div :style="CollapseStream" class="streaming">
      <video-player
        class="vjs-custom-skin"
        ref="videoPlayer"
        :options="playerOptions"
        @ready="onPlayerReadied"
        @timeupdate="onTimeupdate"
      >
      </video-player>
    </div>
    <Chat @collapse="collapse"></Chat>
  </div>
</template>

<script>
import videojs from "video.js";
import Chat from "./Chat.vue";
import Vue from "vue";

const myHeader = new Headers({
  "Access-Control-Allow-Origin":
    "http://" + Vue.prototype.$BACKENDURL + ":8080",
  Accept: "application/json",
  "Content-Type": "application/json",
});

// hls plugin for videojs6
/*require('videojs-contrib-hls/dist/videojs-contrib-hls.js') cette ligne casse le programme*/
window.videojs = videojs;

export default {
  components: { Chat },
  data() {
    return {
      isOpen: true,
      initialized: false,
      currentTech: "",
      streams: {
        rtmp: "",
      },
      playerOptions: {
        // videojs and plugin options
        preferFullWindow: true,
        responsive: true,
        autoSetup: true,
        aspectRatio: "16:9",

        autoplay: true,
        controls: true,
        techOrder: ["flash", "html5"],
        sourceOrder: true,
        muted: true,
        language: "en",
        flash: { hls: { withCredentials: false } },
        html5: { hls: { withCredentials: false } },
        sources: [
          {
            withCredentials: false,
            type: "application/x-mpegURL",
            src: "",
          },
        ],
        poster: "https://i.ibb.co/4R5J8G6/Dessin-sans-titre-3-1.png",
        notSupportedMessage:
          " Le stream n'est pas disponnible. Veuillez réessayer plus tard.",
      },
    };
  },
  methods: {
    getStreamUrl() {
      return fetch(
        "http://" +
          Vue.prototype.$BACKENDURL +
          ":8080/stream/get/" +
          Vue.prototype.$roomID +
          "/" +
          Vue.prototype.$userID,
        { method: "get", headers: myHeader }
      ).then((res) => {
        return res.json().then((o) => {
          return o["url"];
        });
      });
    },
    onPlayerReadied() {
      if (!this.initialized) {
        this.initialized = true;
        this.currentTech = this.player.techName_;
      }
    },
    // record current time
    onTimeupdate() {},
    collapse(e) {
      this.isOpen = e;
    },
  },
  beforeMount() {
    this.getStreamUrl().then((a) => {
      console.log("OOOOOOOOOOOOOH");
      var streamSource = a;
      console.log(streamSource);
      this.playerOptions.sources[0].src = a;
    });
    //this.forceRefresh();
  },
  mounted() {},
  computed: {
    CollapseStream() {
      if (this.isOpen) {
        return {
          width: "80%",
        };
      } else {
        return {
          width: "100%",
        };
      }
    },
  },
};
</script>

<style scoped>
h2 {
  font-size: 3vh;
}
.streaming {
  float: left;
  width: 100%;
  z-index: -1;
  padding-top: 3%;
  color: white;
}
@media only screen and (max-width: 800px) {
  .streaming {
    width: 100% !important;
    height: 100% !important;
    padding-top: 13%;
  }
}
</style>