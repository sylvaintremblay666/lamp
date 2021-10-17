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
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
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
  <!--script src="https://cdn.jsdelivr.net/npm/lodash.debounce@4.0.8/index.js"></script-->
  <script>

Vue.component('mainCompo', {
  template: `
    <div class="d-flex justify-center" style="background-color: #DDD;">
     <!--v-card class="ma-2 pa-2 flex-grow-1" style=""-->
     <div>
       <v-card rounded class="ma-2">
         <h1 class="d-flex justify-center mb-2">Hello {{ServerName}} !</h1>
       </v-card>
        <div class="flex-column">

          <!-- Lights selector -->
          <v-card rounded class="ma-2">
            <h2 class="text-center">Lamp Control</h2>
            <v-row no-gutters class="mb-2 mr-3 justify-center align-center">

              <v-col
                style="max-width: 400px; min-width: 300px; border:0px solid black; border-radius: 20px;background-color: #F0F0F0; line-height: 0.5;"
                class="ml-3 my-2 pt-4 pb-3 justify-center align-center d-flex flex-column"
              >

                <div>
                  <v-row no-gutters class="d-flex justify-center" style="height: 30px;">
                    <v-icon :style="getLEDStyle(0)" class="notransition" @click="ledClick(0)">circle</v-icon>
                    <span class="d-flex justify-center" style="width: 190px; font-size: 16px;">LEDs</span>
                    <v-icon :style="getLEDStyle(7)" @click="ledClick(7)">circle</v-icon>
                  </v-row>

                  <v-row no-gutters class="d-flex justify-center" style="height: 25px;">
                    <v-icon :style="getLEDStyle(1)" @click="ledClick(1)">circle</v-icon>
                    <v-spacer class="" style="max-width:140px;"/>
                    <v-icon :style="getLEDStyle(6)" @click="ledClick(6)">circle</v-icon>
                  </v-row>

                  <v-row no-gutters class="d-flex justify-center" style="height: 25px;">
                    <v-icon :style="getLEDStyle(2)" @click="ledClick(2)">circle</v-icon>
                    <v-spacer class="" style="max-width: 80px;"/>
                    <v-icon :style="getLEDStyle(5)" @click="ledClick(5)">circle</v-icon>
                  </v-row>

                  <v-row no-gutters class="d-flex justify-center" style="height: 15;">
                    <v-icon :style="getLEDStyle(3)" @click="ledClick(3)">circle</v-icon>
                    <v-spacer class="" style="max-width: 15px;"/>
                    <v-icon :style="getLEDStyle(4)" @click="ledClick(4)">circle</v-icon>
                  </v-row>
                </div>

                <div class="d-flex justify-space-around pt-4">
                  <v-btn
                    class="mr-1"
                    rounded
                    small
                    @click="selectAll"
                  >
                    Select All
                  </v-btn>
                  <v-btn
                    class="ml-1"
                    rounded
                    small
                    @click="unselectAll"
                  >
                    UnSelect All
                  </v-btn>
                </div>
              </v-col>

              <div class="d-flex flex-grow-1 flex-column ml-3 mt-3 align-center" style="">
                <v-btn
                  class="mb-2"
                  style="width: 100%;"
                  medium
                  rounded
                  @click="selectedLedsOn"
                >
                  Selected: ON
                </v-btn>

                <v-btn
                  class="my-2"
                  medium
                  rounded
                  style="width: 100%;"
                  @click="selectedLedsOff"
                >
                  Selected: OFF
                </v-btn>

                <div class="d-flex align-center justify-start my-4" style="width: 100%;">
                   <v-slider
                     label="Brightness"
                     class="d-flex justify-center"
                     v-model="brightness"
                     @input="setBrightness"
                     hide-details
                     :min="1"
                     :max="150"
                   >
                   </v-slider>
                </div>

                <div class="mt-2">
                  <v-color-picker 
                    width="340"
                    v-model="color" 
                    hide-mode-switch
                    hide-inputs
                    dot-size="20"
                    canvas-height="100"
                    @input="colorChange"
                  />
                </div>
              </div>
            </v-row>
          </v-card>

          <!-- Clocks radio group -->
          <v-card rounded class="ma-2 pa-2">
            <h2 class="text-center">Clock and Calendar</h2>
            <v-row no-gutters class="mb-2 mr-2">
              <v-radio-group 
                v-model="selectedClock.name"
                @change="newClockSelected"
              >
                <v-radio
                  v-for="clockType, key in clockTypes"
                  :key="clockType"
                  :label="clockType"
                  :value="clockType"
                ></v-radio>
              </v-radio-group>

              <!-- Calendar Examples -->
              <div 
                class="d-flex flex-grow-1 justify-center align-center"
              >
                <div 
                  class="d-flex"
                  style="width: 128px; height:64px; background-color: black;" 
                >

                  <!-- Medium clock -->
                  <v-row no-gutters 
                    v-if="selectedClock.id === 1"
                    class="justify-center" 
                  >
                    <v-col style="font-size: 21px; font-family: Arial;" class="mt-n1">
                      <div style="color:#4CB3FA;" class="d-flex justify-center">
                        {{ timeStringSecs }}
                      </div>
                    </v-col>
                  </v-row>

                  <!-- Big clock -->
                  <v-row no-gutters 
                    v-if="selectedClock.id === 2"
                    class="justify-center" 
                    style="line-height: 12px;"
                  >
                    <v-col style="font-size: 40px; font-family: Roboto;" class="mt-4">
                      <div style="color:#4CB3FA;" class="d-flex justify-center">
                        {{ timeString }}
                      </div>
                      <span style="font-size: 14px; color: yellow;" class="d-flex mt-4 justify-center">
                        Mar 12 Sept 2021
                      </span>
                    </v-col>
                  </v-row>

                </div>
              </div>
            </v-row>
          </v-card>
        </div>
     <!--/v-card-->
       </div>
    </div>
  `,

  data() {
    return {
      ServerName: 'DevServer',
      ServerAddress: 'lampserver.local',
      ledIsOn: false,
      brightness: 0,
      ledsStatus: [{}, {}, {}, {}, {}, {}, {}, {}],
      selectedLeds: [true, true, true, true, true, true, true, true],
      clockTypes: [],
      clockTypeGroup: 0,
      selectedClock: {
        name: "",
        id: 0,
      },
      timeString: '--:--',
      timeStringSecs: '--:--:--',
      color: { 
        r: 255,
        g: 255,
        b: 0,
      },
    }
  },
  async created() {
    console.log('Created! ');
    const { ledState } = await this.ledStatus();
    console.log('ledState: ', ledState);
    this.ledIsOn = ledState === 'On' ? true : false;

    // Init led array

    // TODO spinner...
    await this.getClockTypes();
    await this.getBrightness();

    setInterval(() => { this.updateTime() }, 1000);
  }, 

  methods: {

    getLEDStyle(ledId) {
      const led = this.ledsStatus[ledId];
      let style = '';

      if (led && led.on) {
        style += `color: rgb(${led.r},${led.g},${led.b});`;
      };

      if (this.selectedLeds[ledId]) {
        style += 'border: 2px solid grey; border-radius: 20px;';
      } else {
        style += 'border: 2px solid white; border-radius: 20px;';
      };

      return style
    },

    selectAll() {
      this.selectedLeds.forEach((_, idx, array) => array[idx] = true);
      this.getPixelsStatus();
    },

    unselectAll() {
      this.selectedLeds.forEach((_, idx, array) => array[idx] = false);
      this.getPixelsStatus();
    },

    selectedLedsOn() {
      this.selectedLeds.forEach((selected, idx) => {
        if (selected) {
          const led = this.ledsStatus[idx];
          led.on = true;
          led.r = this.color.r;
          led.g = this.color.g;
          led.b = this.color.b;
          this.setPixel(idx);
        };
      });
      this.setBrightness();
    },

    selectedLedsOff() {
      this.selectedLeds.forEach((selected, idx) => {
        if (selected) {
          const led = this.ledsStatus[idx];
          led.on = false;
          led.r = 0;
          led.g = 0;
          led.b = 0;
          this.setPixel(idx);
        };
      });
      this.setBrightness();
    }, 

    ledClick(ledId) {
      console.log("ledClick!! : ", ledId);

      this.selectedLeds[ledId] = !this.selectedLeds[ledId];
      this.getPixelsStatus();
      return;

      /*
      this.ledsStatus[ledId].on = !this.ledsStatus[ledId].on;
      if (this.ledsStatus[ledId].on) {
        const led = this.ledsStatus[ledId];
        led.r = this.color.r;
        led.g = this.color.g;
        led.b = this.color.b;
      }

      this.setPixel(ledId);
      */
    },

    updateTime() {
      const hh = new String(new Date().getHours()).padStart(2, '0');
      const mm = new String(new Date().getMinutes()).padStart(2, '0');
      const ss = new String(new Date().getSeconds()).padStart(2, '0');
      this.timeString = `${hh}:${mm}`;
      this.timeStringSecs = `${hh}:${mm}:${ss}`;
      this.getPixelsStatus();
    },

    async colorChange() {
      console.log("colorChange!");
      this.selectedLeds.forEach((selected, idx) => {
        if (selected) {
          const led = this.ledsStatus[idx];
          led.r = this.color.r;
          led.g = this.color.g;
          led.b = this.color.b;
          this.setPixel(idx);
        };
      });
      this.getPixelsStatus();
    },

    async getClockTypes() {
      console.log("getClockTypes");
      const response = await this.GetRequest('/clocks');
      const { clockTypes, selectedClock } = await response.json();
      console.log('clockTypes   ---> ', clockTypes);
      console.log('selectedClock   ---> ', selectedClock);
      this.clockTypes = clockTypes;
      // Vue.set(this.selectedClock, 'name', clockTypes[selectedClock]);
      this.selectedClock.name = clockTypes[selectedClock];
      this.selectedClock.id = selectedClock;
      console.log(this.selectedClock);
    },

    async getPixelsStatus() {
      // console.log("getPixelsStatus");
      const response = await this.GetRequest('/pixels/status');
      const status = await response.json();
      this.ledsStatus = status.pixels;
      // console.log(this.ledsStatus);
    },

    async setPixel(pixelId) {
      // console.log("getPixelsStatus");
      const pixel = this.ledsStatus[pixelId];
      const response = await this.GetRequest('/pixel/set', { 'r': pixel.r, 'g': pixel.g, 'b': pixel.b, 'on': pixel.on, 'pixelId': pixelId });
      console.log(response);
      // const status = await response.json();
      // this.ledsStatus = status.pixels;
      //console.log(this.selectedClock);
    },

    async newClockSelected() {
      console.log("newClockSelected!");
      const clockId = this.clockTypes.indexOf(this.selectedClock.name);
      const response = await this.GetRequest('/clock/select', { 'clockId': clockId });
      this.selectedClock.id = clockId;
      console.log(response);
    },

    async setBrightness() {
      console.log("setBrightness!");
      const response = await this.GetRequest('/lamp/brightness/set', { 'value': this.brightness });
      console.log(response);
    },

    async getBrightness() {
      console.log("getBrightness");
      const response = await this.GetRequest('/lamp/brightness');
      const { brightness } = await response.json();
      console.log('current brightness ---> ', brightness);
      this.brightness = brightness;
    },

    async switchStatusLed() {
      console.log('-> switchStatusLed');
      if (this.ledIsOn) {
        await this.GetRequest('/led/on');
      } else {
        await this.GetRequest('/led/off');
      }
    }, 

    async ledStatus() {
      console.log('-> ledStatus');
      const response = await this.GetRequestJson('/led');
      return response;
    },

    async GetRequest(path, params) {
      const url = new URL (`http://${this.ServerAddress}${path}`);
      // console.log('request: ', url)
      if (params) {
        console.log('params: ', params)
        url.search = new URLSearchParams(params);
      }

      const response = await fetch(url);
      // console.log('response: ', response);
      return response;
    },

    async GetRequestJson(path) {
      const response = await this.GetRequest(path);
      const json = await response.json();
      console.log('json: ', json);
      return json;
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

<style scoped>
.notransition {
  -webkit-transition: none !important;
  -moz-transition: none !important;
  -o-transition: none !important;
  transition: none !important;
}
</style>

</style>
</body>
</html>
)=====";

#endif /* INDEX_H_ */
