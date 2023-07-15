'use strict'

const currentScript = document.currentScript

document.addEventListener('DOMContentLoaded', function () {
  document.querySelector('#btn-presentation').addEventListener('click', function () {
    loadAssets(runPresentation)
  })

  function loadAssets (onload) {
    const assetsUrl = currentScript.src.match(/.*\//)

    console.log('Loading reveal.js and presentation.css...')

    const link = document.createElement('link')
    link.rel = 'stylesheet'
    link.type = 'text/css'
    link.media = 'screen'
    link.href = assetsUrl + 'presentation.css'
    document.head.appendChild(link)

    const script = document.createElement('script')
    script.src = assetsUrl + 'reveal.js'
    script.onload = onload
    document.head.appendChild(script)
  }

  function runPresentation () {
    addPresentationContent()
    cleanOriginalContent()
    configureReveal()
  }

  function addPresentationContent () {
    const lecture = getLectureInfo()

    // Add reveal container
    const revealContainer = document.createElement('div')
    revealContainer.classList.add('reveal')
    document.body.appendChild(revealContainer)

    // Add presentation header
    const header = document.createElement('div')
    header.classList.add('header')
    revealContainer.appendChild(header)

    const presentationHeading = document.createElement('span')
    presentationHeading.classList.add('presentation-heading')
    presentationHeading.textContent = lecture.title
    header.appendChild(presentationHeading)

    const endButton = document.createElement('button')
    endButton.id = 'btn-end-presentation'
    endButton.textContent = document.querySelector('#btn-presentation').getAttribute('data-end-msg')
    const pageUrl = window.location.href
    endButton.addEventListener('click', function () {
      window.location.replace(pageUrl)
      window.location.reload()
    })
    header.appendChild(endButton)

    // Add main container
    const slidesContainer = document.createElement('div')
    slidesContainer.classList.add('slides')
    revealContainer.appendChild(slidesContainer)

    // Add first slide with title
    const sectionTitle = document.createElement('section')
    sectionTitle.classList.add('title')
    sectionTitle.innerHTML = '<h1>' + lecture.title + '</h1>'
    slidesContainer.appendChild(sectionTitle)

    // Add second slide with preamble content, if present
    const sectionPreamble = document.querySelector('body > .wrap > .horizont > main > section#preamble')
    if (sectionPreamble) {
      slidesContainer.appendChild(sectionPreamble)
    }

    // Add other slides
    const sectionsLevel1 = document.querySelectorAll('.wrap > .horizont > main > section.level-1')
    sectionsLevel1.forEach(function (section1) {
      // wrap admonitions with <div> tag instead with <section>
      const admonitions = section1.querySelectorAll('section.admonition-block')
      admonitions.forEach(function (admonition) {
        const div = document.createElement('div')
        div.innerHTML = admonition.innerHTML
        admonition.parentNode.replaceChild(div, admonition)
      })

      // Update sections nesting - convert
      //
      // <section>
      //   A
      //   <section>B</section>
      //   <section>C</section>
      // </section>
      //
      // to
      //
      // <section>
      //   <section>A</section>
      //   <section>B</section>
      //   <section>C</section>
      // </section>
      const sectionsLevel2 = section1.querySelectorAll('section.level-2')
      if (sectionsLevel2.length > 0) {
        const slide = document.createElement('section')
        slide.classList.add('level-1')
        slidesContainer.appendChild(slide)

        let firstSubSlide = null
        sectionsLevel2.forEach(function (section2) {
          slide.appendChild(section2)
          if (firstSubSlide === null) {
            firstSubSlide = section2
          }
        })

        section1.classList.remove('level-1')
        section1.classList.add('level-2')
        slide.insertBefore(section1, firstSubSlide)
      } else {
        slidesContainer.appendChild(section1)
      }
    })

    // Add presentation footer
    const footer = document.createElement('div')
    footer.classList.add('footer')
    revealContainer.appendChild(footer)

    const tutorialSource = document.createElement('span')
    tutorialSource.classList.add('tutorial-source')
    tutorialSource.textContent = lecture.source
    footer.appendChild(tutorialSource)

    const meta = document.createElement('span')
    meta.classList.add('meta')
    meta.innerHTML = lecture.courseCode + ' ' + lecture.courseName + ' &bull; '
    meta.appendChild(lecture.timeEl)
    footer.appendChild(meta)
  }

  function getLectureInfo () {
    const courseHeading = document.querySelector('.wrap > .header > .heading-group > .course-heading')

    return {
      title: document.querySelector('body > .wrap > .horizont > main > h1').textContent.trim(),
      courseCode: courseHeading.firstChild.textContent.trim(),
      courseName: courseHeading.querySelector('.fullname').textContent.trim(),
      source: document.querySelector('.page-footer > .wrap > .meta > a').textContent.trim(),
      timeEl: document.querySelector('.page-footer > .wrap > .meta > a > time'),
    }
  }

  function cleanOriginalContent () {
    document.querySelector('body > .wrap').remove()
    document.querySelector('body > footer').remove()
  }

  function configureReveal () {
    /* eslint-disable no-undef */
    Reveal.initialize({
      width: '100%',
      height: '100%',
      controlsTutorial: false,
      center: false,
      transition: 'none',
      history: true,
    })
  }
})
