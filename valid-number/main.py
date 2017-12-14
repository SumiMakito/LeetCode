class Solution(object):
    def isNumber(self, s):
        """
        :type s: str
        :rtype: bool
        """
        valid = False
        sn = False
        dcm = False
        sgn = False
        s = s.strip()
        if len(s) == 0:
            return False
        for c in s:
            if c.isdigit():
                sgn = True
                valid = True
            elif not dcm and c == ".":
                dcm = True
                sgn = True
            elif valid and not sn and (c == "e" or c == "E"):
                dcm = True
                sgn = False
                sn = True
                valid = False
            elif not sgn and (c == "-" or c == "+"):
                sgn = True
            else:
                return False
        return valid