document.addEventListener('DOMContentLoaded', function () {
  /*
   *  Display a list of available archived versions (semesters)
   */
  var currentPath = decodeURIComponent(window.location.pathname).split('/')
  var branchesPath = ['', currentPath[1], '.branches.json'].join('/')

  var req = new XMLHttpRequest()
  req.open('GET', branchesPath, true)
  req.onload = function () {
    if (req.status >= 200 && req.status < 400) {
      var branches = JSON.parse(req.responseText)

      var semestersHTML = branches
        .filter(function (item) { return item.branch !== 'master' })
        .map(function (item) {
          return '<a href="' + item.url + '">' + item.branch + '</a>'
        })
        .join(', ')

      // Display the semester selector
      document.querySelector('#semesters-list').innerHTML = semestersHTML
    }
  }
  req.send()
})
