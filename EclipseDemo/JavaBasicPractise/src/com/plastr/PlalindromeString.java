package com.plastr;

/**
 * @author xiaoshi on 2018/9/24. Happy Mid-Autumn Festival
 */
public class PlalindromeString {

	// �ж�һ���ַ����Ƿ���ģ��㷨���ò�����
	@Deprecated
	private boolean isPlalindrome(String s) {
		int len = s.length();
		for (int i = 0; i < len / 2; i++) {
			if (s.charAt(i) != s.charAt(len - 1 - i)) {
				return false;
			}
		}
		return true;
	}

	// Ԥ�����ַ������������ַ�֮�����#
	private String preHandleString(String s) {
		StringBuffer sb = new StringBuffer();
		int len = s.length();
		sb.append('#');
		for (int i = 0; i < len; i++) {
			sb.append(s.charAt(i));
			sb.append('#');
		}
		return sb.toString();
	}

	// Ѱ��������ִ�
	public String findLongestPlalindromeString(String s) {
		// ��Ԥ�����ַ���
		String str = preHandleString(s);
		// �������ִ�����
		int len = str.length();
		// �ұ߽�
		int rightSide = 0;
		// �ұ߽��Ӧ�Ļ��Ĵ�����
		int rightSideCenter = 0;
		// ������ÿ���ַ�Ϊ���ĵĻ��ĳ���һ�루����ȡ����
		int[] halfLenArr = new int[len];
		// ��¼��������
		int center = 0;
		// ��¼����ĳ���
		int longestHalf = 0;
		for (int i = 0; i < len; i++) {
			// �Ƿ���Ҫ������չ
			boolean needCalc = true;
			// ������ұ߽�ĸ���֮��
			if (rightSide > i) {
				// �������rightSideCenter�ĶԳ�λ��
				int leftCenter = 2 * rightSideCenter - i;
				// ���ݻ������ʵõ��Ľ���
				halfLenArr[i] = halfLenArr[leftCenter];
				// ����������ұ߽磬���е���
				if (i + halfLenArr[i] > rightSide) {
					halfLenArr[i] = rightSide - i;
				}
				// ���������֪��������ó��������С���ұ߽磬����Ҫ��չ��
				if (i + halfLenArr[leftCenter] < rightSide) {
					// ֱ���Ƴ�����
					needCalc = false;
				}
			}
			// ������չ
			if (needCalc) {
				while (i - 1 - halfLenArr[i] >= 0 && i + 1 + halfLenArr[i] < len) {
					if (str.charAt(i + 1 + halfLenArr[i]) == str.charAt(i - 1 - halfLenArr[i])) {
						halfLenArr[i]++;
					} else {
						break;
					}
				}
				// �����ұ߽缰����
				rightSide = i + halfLenArr[i];
				rightSideCenter = i;
				// ��¼����Ĵ�
				if (halfLenArr[i] > longestHalf) {
					center = i;
					longestHalf = halfLenArr[i];
				}
			}
		}
		// ȥ��֮ǰ��ӵ�#
		StringBuffer sb = new StringBuffer();
		for (int i = center - longestHalf + 1; i <= center + longestHalf; i += 2) {
			sb.append(str.charAt(i));
		}
		return sb.toString();
	}

}
