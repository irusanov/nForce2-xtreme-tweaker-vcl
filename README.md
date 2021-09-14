<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/irusanov/nForce2-xtreme-tweaker-vcl">
    <img src="icon-48.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">nForce2-xtreme-tweaker-vcl</h3>

  <p align="center">
    A new generation tweaker for the NVidia nForce2 motherboards.
    <br />
    <a href="https://github.com/irusanov/nForce2-xtreme-tweaker-vcl"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/issues">Report Bug</a>
    ·
    <a href="https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![nForce2XT Screen Shot][product-screenshot]](https://example.com)

The project aims to provide an extensive control of all known and newly discovered parameters of nForce2-based motherboards for AMD's socket A (462) CPUs.

The goal is to have a single app to control timings, chipset settings and ROMSIP registers, FSB and AGP/PCI frequencies. All that with the ability to save and load own profiles for easier overclocking.

It is the result of a 2-years research and reverse-engineering, with the great help from members of @hardwareLuxxx and @hwbot forums.

### Built With

The app is built with Embarcadero C++ Builder Community Edition and uses Openlibsys' WinRing0 to communicate with the PCI bus.
A modified and enhanced version of the cpufreq-nforce2 driver is also used in order to control the integrated PLL.
* [C++ Builder Community Edition](https://www.embarcadero.com/products/cbuilder/starter/)
* [OpenLibsys](https://openlibsys.org/manual/)
* [cpufreq-nforce2 linux kernel driver](https://github.com/torvalds/linux/blob/master/drivers/cpufreq/cpufreq-nforce2.c)



<!-- GETTING STARTED -->
## Getting Started

No installation is required, the application is portable and distributed as an archive, containing required binaries.

### Prerequisites


* Supported operating systems are Windows 2000 and newer.
* A motherboard with nForce2 chipset
* [Microsoft Visual C++ 2005 Redistributable Package](https://www.microsoft.com/en-us/download/details.aspx?id=26347)


### Installation

1. Install the VC++ 2005 redistributable package [Downlod from Microsoft site](https://www.microsoft.com/en-us/download/details.aspx?id=26347)
2. Unzip the application
3. Run NForce2Xtreme.exe

It is possible to run on an unsupported system, but you need to compile it as ```DEBUG```. 64-bit systems also required the x64 WinRing0 binaries. This is only useful for development.



<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Your Name - [@your_twitter](https://twitter.com/your_username) - email@example.com

Project Link: [https://github.com/irusanov/nForce2-xtreme-tweaker-vcl](https://github.com/irusanov/nForce2-xtreme-tweaker-vcl)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Animate.css](https://daneden.github.io/animate.css)
* [Loaders.css](https://connoratherton.com/loaders)
* [Slick Carousel](https://kenwheeler.github.io/slick)
* [Smooth Scroll](https://github.com/cferdinandi/smooth-scroll)
* [Sticky Kit](http://leafo.net/sticky-kit)
* [JVectorMap](http://jvectormap.com)
* [Font Awesome](https://fontawesome.com)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/irusanov/nForce2-xtreme-tweaker-vcl.svg?style=for-the-badge
[contributors-url]: https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/irusanov/nForce2-xtreme-tweaker-vcl.svg?style=for-the-badge
[forks-url]: https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/network/members
[stars-shield]: https://img.shields.io/github/stars/irusanov/nForce2-xtreme-tweaker-vcl.svg?style=for-the-badge
[stars-url]: https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/stargazers
[issues-shield]: https://img.shields.io/github/issues/irusanov/nForce2-xtreme-tweaker-vcl.svg?style=for-the-badge
[issues-url]: https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/issues
[license-shield]: https://img.shields.io/github/license/irusanov/nForce2-xtreme-tweaker-vcl.svg?style=for-the-badge
[license-url]: https://github.com/irusanov/nForce2-xtreme-tweaker-vcl/blob/master/LICENSE.txt
[product-screenshot]: images/screenshot.png
