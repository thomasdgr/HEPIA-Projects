<template>
  <div id="app">
    <NavBar/>
    <Stream msg="Lolixdé"/>
  </div>
</template>

<script>

import Stream from './components/Stream.vue'
import 'video.js/dist/video-js.css'
import NavBar from '@/components/NavBar'
//import Chat from '@/components/Chat'
import Vue from 'vue'

Vue.prototype.$Chat = true
export default {
  name: 'App',
  components: {
    NavBar,
    Stream,
  }
}

</script>

<style>

html {
  background-color: #6f30a0;
  height: 100%;
  width: 100%;
}
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  background-color: #6f30a0;
  
}
</style>
