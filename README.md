# Ray-Traced Audio for Accessibility (Unreal Engine 5)

## 📌 Introduction
Ray-traced audio is a technology that is still in its early stages of development, enabling the simulation of the complex physics of sound waves, such as reflection, occlusion, and diffraction. Unfortunately, this technology is currently limited to enhancing immersion strictly for hearing players. 

The aim of this research project is to explore a way of using audio ray tracing metadata to create precise and immersive visual feedback for deaf and hard-of-hearing players.


<img width="540" height="303" alt="AccessibilityTest-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/9018c369-2711-40bc-b33a-43bde1a214c6" />

---

## 🔍 State of the Art

### The Audio Landscape
Currently, spatial audio in video games is divided into two main categories:
* **Baked Solutions:** Systems like Microsoft Project Acoustics and Microsoft TRITON / Snowdrop engine. These are utilized in AAA titles such as *Gears of War 4* and *Avatar: Frontiers of Pandora* to simulate sound behavior in varied spaces.
* **Real-Time Solutions:** Hardware-accelerated path-traced audio like NVIDIA VRWorks Audio and AMD TrueAudio. A prime example in modern gaming is *Returnal*. Other popular spatial calculation tools include Steam Audio and Unreal Engine's MetaSounds.

### Classic Accessibility
Current audio accessibility relies heavily on geometric 2D space rather than true physical sound propagation. 
* **Competitive Games:** Titles like *Fortnite* use a circular, radial HUD to show the direction of footsteps or gunfire. While easy to read, it remains a very primary system.
* **Narrative Games:** Titles like *The Last of Us Remastered* and *Minecraft* rely on directional audio subtitles. While better integrated into the HUD, this breaks immersion and demands specific attention from deaf players.

---

## 🛠️ Approach & Analysis

The core of this project relies on a line trace system built in Unreal Engine 5 to map audio physics into a visual space. Throughout the R&D process, three distinct architectures were tested to find the best balance between accurate spatial visualization and hardware performance.


### V1: Deferred Decals
This initial approach spawned a decal at every hit location of the audio line trace.
* **Performance:** ~31 FPS.
* **PROS:** Easy to implement; effectively shapes with the level geometry.
* **CONS:** Causes stutters when spawning massive amounts of decals; hard to customize; not future-proof as it strictly needs a surface to exist (cannot display floating diffraction sound).
<img width="500" height="214" alt="V1PerformanceTestCrop-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/c5be2316-2e94-4551-a593-591b748ca366" />
---
### V2: Individual Particles
To avoid the surface limitations of V1, this iteration spawned individual Niagara particle systems per hit.
* **Performance:** ~62 FPS.
* **PROS:** No need for geometry, allowing sound to float in space; particles maintain their own individual life cycle.
* **CONS:** Really heavy performance-wise due to the massive amount of systems being spawned and destroyed; hard to customize globally.
<img width="500" height="214" alt="V2PerformanceTestCrop-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/9f37b306-deb2-477e-9189-cb8b3f4630c8" />
---

### V3: Compute Shaders (Core System)
The final and most optimized approach relies on a data-driven architecture. The line traces collect hit coordinates (World Locations) into arrays, which are then fed into a single Niagara system via Compute Shaders.
* **Performance:** ~80 FPS.
* **PROS:** Highly optimized; ensures massive scalability regardless of the amount of audio sources.
* **CONS:** Hard to adapt the code due to shader complexity; loses the individual particle life cycle (all points fade out uniformly).
<img width="500" height="214" alt="V3PerformanceTestCrop-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/8a666117-3324-42aa-b55f-17d9298176aa" />

---

## 📚 Bibliography
* [A First Look At Raytraced Audio](https://www.youtube.com/watch?v=O12z01x3qEo)
* [Microsoft Project Acoustics](https://aka.ms/acoustics)
* [AMD Ray Traced VR Audio](https://www.amd.com)
* [Steam Audio](https://valvesoftware.github.io/steam-audio/)
* [Meta Acoustic Ray Tracing SDK](https://developer.oculus.com/documentation/unity/audio-acoustic-ray-tracing/)
* [Vercidium Audio](https://vercidium.com/blog/audio-tracing/)
* [Realtime Audio Raytracing and Occlusion in Csound and Unity](https://csound.com/icsc2022/proceedings/Realtime%20Audio%20Raytracing%20and%20Occlusion%20in%20Csound%20and%20Unity.pdf)
* [Ray tracing audio in snowdrop creating a living pandora](https://www.massive.se/blog/news/ray-tracing-audio-in-snowdrop-creating-a-living-pandora/)
