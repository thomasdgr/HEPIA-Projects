import Vue from 'vue'
import App from './App.vue'
import VueVideoPlayer from 'vue-video-player'
import io from "socket.io-client";

Vue.config.productionTip = false
Vue.use(VueVideoPlayer)

Vue.prototype.$userID = prompt("prompt", "textbox's intial text");
Vue.prototype.$io = io;
Vue.prototype.$roomID = location.href.substring(location.href.lastIndexOf('/')+1);


Vue.prototype.$BACKENDURL = "localhost";

//Vue.prototype.$BACKENDPORT = "8080";
//Vue.prototype.$CHATPORT = "3000";


new Vue({
  render: h => h(App),
}).$mount('#app')
