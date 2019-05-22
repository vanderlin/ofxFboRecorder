# ofxFboRecorder
A very simple addon for making videos from a fbo.

![alt text](https://github.com/vanderlin/ofxFboRecorder/blob/master/images/export.gif "Example Image")

## FFmpeg Commands
**Make a video from a sequence**  
`ffmpeg -framerate 60 -i frame_%d.png -crf 10 -vf 'setpts=1.0*PTS' -pix_fmt yuv420p -c:a copy -tune grain export.mov`


**Make a nice fade out on audio**   
`ffmpeg -i test02.mp3 -af "afade=t=out:st=65:d=5" test03.mp3`


`ffmpeg -framerate 60 -i 0000%3d.png -crf 10 -vf 'setpts=1.0*PTS' -pix_fmt yuv420p -c:a copy -tune grain export.mov`


**make a gif to a mp4**   
`ffmpeg -i file.gif -pix_fmt yuv420p out.mp4`
