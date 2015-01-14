{
  "targets": [
  {
    "target_name": "userid",
      "sources": [ "src/userid.cc" ],
      "include_dirs" : [
          "<!(node -e \"require('nan')\")"
      ]
  }
  ]
}
