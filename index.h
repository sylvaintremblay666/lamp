/*
 * index.h
 *
 *  Created on: Sep 25, 2021
 *      Author: stremblay
 */

#ifndef INDEX_H_
#define INDEX_H_

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <link href="https://fonts.googleapis.com/css?family=Roboto:100,300,400,500,700,900" rel="stylesheet">
  <link href="https://cdn.jsdelivr.net/npm/@mdi/font@4.x/css/materialdesignicons.min.css" rel="stylesheet">
  <link href="https://cdn.jsdelivr.net/npm/vuetify@2.x/dist/vuetify.min.css" rel="stylesheet">
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no, minimal-ui">
</head>
<body>
  <div id="app">
    <v-app>
      <v-main>
          <!--<v-container>Hello </v-container> -->
          <!--
        <v-progress-circular indeterminate color="red" />
        <v-btn @click="toto">Button!</v-btn>
          -->
        <main-compo />
      </v-main>
    </v-app>
  </div>

  <script src="https://cdn.jsdelivr.net/npm/vue@2.x/dist/vue.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/vuetify@2.x/dist/vuetify.js"></script>
  <script>

Vue.component('mainCompo', {
  template: `
    <div>
     <v-card class="ma-2 pa-2" style="max-width: 800px;">
       <h1>Hello {{ServerName}} !</h1>
        <v-btn @click="toggleLed">Toggle Led</v-btn>
     </v-card>
    </div>
  `,
  data() {
    return {
      ServerName: 'DevServer',
      ServerAddress: 'lampserver.local',
    }
  },
  methods: {
    async toggleLed() {
      console.log('-> toggleLed');
      const response = await this.GetRequest('/led/toggle');
    },

    async GetRequest(path) {
      const url = `http://${this.ServerAddress}${path}`;
      console.log('request: ', url)

      const response = await fetch(url);
      console.log('response: ', response);
      return response;
    },
  },
})


    new Vue({
      el: '#app',
      vuetify: new Vuetify(),
      methods: {
        toto() {
          console.log('Toto!');
        },
      },
    })
  </script>
</body>
</html>
)=====";

#endif /* INDEX_H_ */
