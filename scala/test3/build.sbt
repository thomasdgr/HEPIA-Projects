val scala3Version = "3.1.0"

lazy val root = project
  .in(file("."))
  .settings(
    name := "hepiascala_eval3",
    version := "2.0.0",
    scalaVersion := scala3Version,
    libraryDependencies ++= Seq(
      "org.scalatest" %% "scalatest" % "3.2.9" % Test
    ),
    Compile / scalaSource := baseDirectory.value / "src",
    Test / scalaSource := baseDirectory.value / "test-src"
  )
