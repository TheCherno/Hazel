-- Clean Function
newaction {
	trigger     = "clean",
	description = "clean build files",
	execute     = function ()
		print("clean the build...")
		os.rmdir("./bin")
		os.rmdir("./bin-int")
		print("done.")
	end
}