module.exports = function(grunt) {

  grunt.initConfig({
   arduino: {
     options: {
       sketch: 'siva-utp/siva-utp.ino',
       idePath: '/home/jose/Tools/arduino-1.8.3/arduino'
     },
     settings: {
       options: {
         savePrefs: true,
         port: '/dev/ttyACM1',
         board: {
           package: 'arduino',
           arch: 'avr',
           board: 'mega'
         }
       }
     },
     verify: {
       options: {
         action: 'verify'
       }
     },
     upload: {
       options: {
         action: 'upload'
       }
     }
   },
  });

  grunt.loadNpmTasks('grunt-arduino');
};
