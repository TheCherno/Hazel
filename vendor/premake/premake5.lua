
function FileExists(filename)
	local filehandle=io.open(filename,"r")
	if filehandle~=nil then
		io.close(filehandle)
		return true
	else
		return false
	end
end

project "Premake"
	kind "Utility"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{wks.location}/**premake5.lua"
	}

	if FileExists("bin/premake5.exe") then
		postbuildmessage "Regenerating project files with Premake5!"
		postbuildcommands
		{
			"\"%{prj.location}bin/premake5\" %{_ACTION} --file=\"%{wks.location}premake5.lua\""
		}
	end
